#include "Go/pch.h"
//
#include "MatchManager.h"
//

namespace Server
{
using namespace Networking::Message;

MatchManager::MatchManager(const Match &match) : mMatch(make_shared<Match>(match))
{
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

void MatchManager::ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message)
{
}
} // namespace Server
