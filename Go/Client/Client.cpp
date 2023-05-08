#include "Go/pch.h"

#include "Client.h"

namespace Client
{
using namespace Networking::Client;

Client::Client(IOContext &context) : mContext(context), mClient(mContext.CreateSocket())
{
}

void Client::Start(const string &ip, const port_type port, function<void(ContextServerInit)> callbackInit,
                   function<void(ContextServer)> callback)
{
    auto &&resolver = mContext.CreateResolver();
    auto endpoints = resolver.resolve({make_address(ip), port});

    mClient.Connect(endpoints, [=, this](const auto &ec, const auto &) {
        if (ec)
        {
            return;
        }

        decltype(callback) callbackReceive = [=, this](const auto &context) {
            callback(context);
            Receive(callbackReceive);
        };

        Init([=, this](const auto &playerColor) {
            callbackInit(playerColor);
            Receive(callbackReceive);
        });
    });
}

void Client::Init(function<void(ContextServerInit)> callback)
{
    mClient.Receive([callback = move(callback)](const auto &, const auto &messageDisassembled) {
        auto &jsonString = *reinterpret_cast<string *>(get<2>(*messageDisassembled).data());

        ContextServerInit context({0, Coord{0, 0}}, Player::Color::NONE);
        context.from_json(json::parse(jsonString), context);
        callback(context);
    });
}

void Client::Send(ContextClient &context)
{
    json contextJSON;
    context.to_json(contextJSON, context);

    mClient.Send(*reinterpret_cast<TCPClient::bytes *>(contextJSON.dump().data()), HeaderMetadata::Type::TEXT,
                 [](const auto &, const auto &) {});
}

void Client::Receive(function<void(ContextServer)> callback)
{
    mClient.Receive([callback = move(callback)](const auto &, const auto &messageDisassembled) {
        auto &jsonString = *reinterpret_cast<string *>(get<2>(*messageDisassembled).data());

        ContextServer context(Coord{0, 0}, {});
        context.from_json(json::parse(jsonString), context);
        callback(context);
    });
}
} // namespace Client
