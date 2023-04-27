#include "Go/pch.h"

#include "Go/Game/Stone.h"
#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/Message/MessageConverter.h"
#include "Gome/Utility/Random.h"
#include "Match.h"
#include "MatchManager.h"

namespace Server
{
using namespace Networking;
using namespace Client;
using namespace Message;
using namespace Game;

MatchManager::MatchManager(const vector<shared_ptr<TCPClient>> &clients, const uint8_t playersPerMatch,
                           const Coord &size)
{
    mMatch = make_shared<Match>(move(CreateMatch(clients, playersPerMatch, size)));
}

Match MatchManager::CreateMatch(vector<shared_ptr<TCPClient>> clients, const uint8_t playersPerMatch, const Coord &size)
{
    vector<Player> players{};
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((unsigned int)seed));

    for (size_t i = 0; i < playersPerMatch; i++)
    {
        Player player((Player::Color)colors[i]);
        players.push_back(player);
    }

    // TODO: not unique stones pos
    Random random;
    for (auto &player : players)
    {
        auto &&sizeValues = size.GetXY();
        auto row = (uint8_t)random.Get((uint16_t)1, (uint16_t)sizeValues.first);
        auto col = (uint8_t)random.Get((uint16_t)1, (uint16_t)sizeValues.second);

        Stone stone(player, {row, col});
        mMatch->mBoard.AddStone(stone);
    }

    return Match(players, size);
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

    return mMatch->mPlayers[indexOfClient];
}

Networking::Message::Message MatchManager::ProcessPlayerMessage(Player & /*player*/,
                                                                shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;
    json bytesAsJSON(bytes);

    return Networking::Message::MessageManager::ToMessage({}, Networking::Message::HeaderMetadata::Type::TEXT);
}
} // namespace Server
