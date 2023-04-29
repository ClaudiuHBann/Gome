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
    for (auto &client : mClients)
    {
        ProcessPlayer(client);
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

Networking::Message::Message MatchManager::ProcessPlayerMessage(Player & /*player*/,
                                                                shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;
    json bytesAsJSON(bytes);

    return Networking::Message::MessageManager::ToMessage({}, Networking::Message::HeaderMetadata::Type::TEXT);
}
} // namespace Server
