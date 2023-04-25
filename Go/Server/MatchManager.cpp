#include "Go/pch.h"

#include "Go/Game/Stone.h"
#include "Gome/Utility/Random.h"
#include "Match.h"
#include "MatchManager.h"

namespace Server
{
using namespace Networking;
using namespace Message;
using namespace Game;

MatchManager::MatchManager(const list<shared_ptr<TCPClient>> &clients, const uint8_t playersPerMatch, const Coord &size)
    : mMatch(make_shared<Match>())
{
    CreateMatch(clients, playersPerMatch, size);
}

void MatchManager::CreateMatch(list<shared_ptr<TCPClient>> clients, const uint8_t playersPerMatch, const Coord &size)
{
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((unsigned int)seed));

    for (size_t i = 0; i < playersPerMatch; i++)
    {
        Player player((Player::Color)colors[i]);
        mMatch->AddPlayer(player);
    }

    // TODO: not unique stones pos
    Random random;
    for (auto &player : mMatch->GetPlayers())
    {
        auto &&sizeValues = size.GetXY();
        auto row = random.Get((uint16_t)1, (uint16_t)sizeValues.first);
        auto col = random.Get((uint16_t)1, (uint16_t)sizeValues.second);
        // player.AddStone({row, col});
    }
}

void MatchManager::Process()
{
    for (auto &player : mMatch->GetPlayers())
    {
        ProcessPlayer(player);
    }
}

void MatchManager::ProcessPlayer(Player &player)
{
    /*player.GetClient()->Receive([&, match = mMatch](auto ec, shared_ptr<MessageManager::MessageDisassembled> message)
    { if (!ec)
        {
            ProcessPlayerMessage(player, message);
        }

        ProcessPlayer(player);
    });*/
}

shared_ptr<TCPClient> MatchManager::GetTCPClient(const Player &player)
{
    for (const auto &client : mClients)
    {
    }

    assert("");
    return nullptr;
}

Networking::Message::Message MatchManager::ProcessPlayerMessage(Player & /*player*/,
                                                                shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;
    json bytesAsJSON(bytes);

    // return {};
}
} // namespace Server
