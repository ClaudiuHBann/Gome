#include "Go/pch.h"

#include "Client.h"

namespace Client
{
using namespace Networking::Client;

Client::Client(IOContext &context, CallbackContextServerInit callbackInit, CallbackContextServer callback,
               CallbackContextServerUninit callbackUninit)
    : mContext(context), mClient(mContext.CreateSocket()), mCallbackInit(move(callbackInit)), mCallback(move(callback)),
      mCallbackUninit(move(callbackUninit))
{
}

void Client::ReceiveProcess(const string &jsonString)
{
    auto contextType = IContext::Type::NONE;
    auto &&json = json::parse(jsonString);
    json.at("mType").get_to(contextType);

    switch (contextType)
    {
    case IContext::Type::SERVER_INIT: {
        ContextServerInit context({0, Coord{0, 0}}, Player::Color::NONE);
        context.FromJSONString(jsonString);
        mCallbackInit(context);
    }
    break;
    case IContext::Type::SERVER: {
        ContextServer context(Coord{0, 0}, {}, ContextServer::Error::NONE, {});
        context.FromJSONString(jsonString);
        mCallback(context);
    }
    break;
    case IContext::Type::SERVER_UNINIT: {
        ContextServerUninit context(Player::Color::NONE, {});
        context.FromJSONString(jsonString);
        mCallbackUninit(context);
    }
    break;
    }
}

void Client::Connect(const string &ip, const uint16_t port)
{
    auto &&resolver = mContext.CreateResolver();
    auto &&endpoints = resolver.resolve(ip, to_string(port));

    TRACE(format("Connecting to {}:{}...", SERVER_IP, SERVER_PORT).c_str());
    mClient.Connect(endpoints, [=, this](const auto &ec, auto) {
        if (ec)
        {
            return;
        }

        TRACE(format("Connected succeesfully to {}:{}.", SERVER_IP, SERVER_PORT).c_str());

        Receive();
    });
}

void Client::Disconnect()
{
    mClient.Disconnect();
}

void Client::Send(ContextClient &context)
{
    auto &&contextJSONString = context.ToJSONString();

    bytes data((byte *)contextJSONString.data(), (byte *)contextJSONString.data() + contextJSONString.size());
    mClient.Send(data, HeaderMetadata::Type::TEXT, [](auto, auto) {});
}

void Client::Receive()
{
    mClient.Receive([this](auto ec, auto messageDisassembled) {
        if (!ec)
        {
            string jsonString((char *)get<2>(*messageDisassembled).data(),
                              (char *)get<2>(*messageDisassembled).data() + get<2>(*messageDisassembled).size());
            ReceiveProcess(jsonString);
        }

        Receive();
    });
}
} // namespace Client
