#include "Go/pch.h"
//
#include "MatchManager.h"
//
#include "Go/json.hpp"
#include "Gome/Utility/Random.h"

namespace Server
{
using namespace Networking;
using namespace Message;
using namespace Client;

using namespace nlohmann;

MatchManager::MatchManager(vector<shared_ptr<TCPClient>> clients) : mMatch(make_shared<Match>())
{
    CreateMatch(clients);
}

void MatchManager::CreateMatch(vector<shared_ptr<TCPClient>> clients)
{
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((unsigned int)seed));

    for (size_t i = 0; i < PLAYERS_PER_MATCH; i++)
    {
        Player player(clients[i], (Player::Color)colors[i]);
        mMatch->AddPlayer(player);
    }

    // TODO: not unique stones pos
    Random random;
    for (auto &player : mMatch->GetPlayers())
    {
        auto row = random.GetInt((size_t)1, TABLE_SIZE_ROWS);
        auto col = random.GetInt((size_t)1, TABLE_SIZE_COLUMNS);
        player.AddStone({row, col});
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
    player.GetClient()->Receive([&, match = mMatch](auto ec, shared_ptr<MessageManager::MessageDisassembled> message) {
        if (!ec)
        {
            ProcessPlayerMessage(player, message);
        }

        ProcessPlayer(player);
    });
}

void MatchManager::ProcessPlayerMessage(Player & /*player*/, shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;
    json bytesAsJSON(bytes);
}

bool MatchManager::IsMoveValid(Player & /*player*/, const Stone & /*stone*/)
{
    return true;
}
} // namespace Server
