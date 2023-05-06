#include "Go/pch.h"

#include "Client.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Client
{
using namespace Networking::Client;

Client::Client(shared_ptr<TCPClient> client) : mClient(client)
{
}

void Client::Start(function<void(Player::Color)> callbackInit, function<void(Board, string)> callback)
{
    decltype(callback) callbackReceive = [this, callback = move(callback), callbackReceive](const auto &board,
                                                                                            const auto &message) {
        callback(board, message);
        Receive(callbackReceive);
    };

    GetPlayerColor(
        [this, callbackInit = move(callbackInit), callbackReceive = move(callbackReceive)](const auto &playerColor) {
            callbackInit(playerColor);
            Receive(callbackReceive);
        });
}

void Client::GetPlayerColor(function<void(Player::Color)> callback)
{
    mClient->Receive([callback = move(callback)](const auto &, const auto &messageDisassembled) {
        auto &jsonString = *reinterpret_cast<string *>(get<2>(*messageDisassembled).data());
        auto &&json = json::parse(jsonString);

        callback(json.at(JSON_PLAYER_COLOR));
    });
}

void Client::Send(const Stone &stone, const Player::Joker joker)
{
    auto &&json = JSONStoneAndJokerTo(stone, joker);
    mClient->Send(*reinterpret_cast<TCPClient::bytes *>(json.dump().data()), HeaderMetadata::Type::TEXT,
                  [](const auto &, const auto &) {});
}

void Client::Receive(function<void(Board, string)> callback)
{
    mClient->Receive([callback = move(callback)](const auto &, const auto &messageDisassembled) {
        auto &&[board, message] =
            JSONBoardAndMessageFrom(*reinterpret_cast<string *>(get<2>(*messageDisassembled).data()));
        callback(board, message);
    });
}
} // namespace Client
