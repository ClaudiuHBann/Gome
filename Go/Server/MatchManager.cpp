#include "Go/pch.h"

#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/Message/MessageConverter.h"
#include "Match.h"
#include "MatchManager.h"

namespace Server
{
using namespace Networking;
using namespace Client;
using namespace Game;

MatchManager::MatchManager(const vector<shared_ptr<TCPClient>> &clients, Match &match)
    : mClients(clients), mMatch(match)
{
}

void MatchManager::Process()
{
    for (size_t i = 0; i < mClients.size(); i++)
    {
        json j;
        j[JSON_PLAYER_COLOR] = mMatch.mPlayers[i].GetColor();
        j[JSON_MATCH_RULES] = mMatch.mRules;

        mClients[i]->Send(*reinterpret_cast<TCPClient::bytes *>(j.dump().data()), HeaderMetadata::Type::TEXT,
                          [this, i = i](const auto &, const auto &) { ProcessPlayer(mClients[i]); });
    }
}

void MatchManager::ProcessPlayer(shared_ptr<TCPClient> client)
{
    client->Receive([&, match = mMatch](auto ec, shared_ptr<MessageManager::MessageDisassembled> messageDisassembled) {
        if (!ec)
        {
            auto &&message = ProcessPlayerMessage(GetPlayerByClient(client), messageDisassembled);
            auto &&messageBytes = Networking::Message::MessageConverter::MessageToBytes(message);
            client->Send(messageBytes, Networking::Message::HeaderMetadata::Type::TEXT, [](auto, auto) {});
        }

        ProcessPlayer(client);
    });
}

Player &MatchManager::GetPlayerByClient(const shared_ptr<TCPClient> &client)
{
    size_t indexOfClient = 0;
    for (; indexOfClient < mClients.size(); indexOfClient++)
    {
        if (client == mClients[indexOfClient])
        {
            break;
        }
    }

    return mMatch.mPlayers[indexOfClient];
}

Networking::Message::Message MatchManager::ProcessPlayerMessage(Player &player,
                                                                shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;
    auto &&[stone, joker] = JSONStoneAndJokerFrom(*reinterpret_cast<string *>(bytes.data()));

    scoped_lock lock(mMutex);

    string jsonMessage;
    if (player != mMatch.GetPlayerCurrent())
    {
        jsonMessage = "Wait your turn!";
    }
    else
    {
        bool setActiveJoker = true;
        if (joker != Player::Joker::NONE)
        {
            setActiveJoker = player.SetActiveJoker(joker);
        }

        if (!setActiveJoker)
        {
            jsonMessage = format("Joker {} is already used!", Player::GetJokerName(joker));
        }
        else
        {
            if (!mMatch.mBoard.AddStone(player, stone))
            {
                jsonMessage = format("Couldn't add stone!", Player::GetJokerName(joker));
            }
            else
            {
                mMatch.GetPlayerNext();
            }
        }
    }

    auto &&json = JSONBoardAndMessageTo(mMatch.mBoard, jsonMessage);
    return Networking::Message::MessageManager::ToMessage(
        *reinterpret_cast<MessageManager::bytes *>(json.dump().data()),
        Networking::Message::HeaderMetadata::Type::TEXT);
}
} // namespace Server
