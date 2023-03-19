#include "Go/pch.h"
//
#include "Match.h"
//

namespace Server
{
void Match::AddPlayer(const Player &player)
{
    mPlayers.push_back(player);
}

vector<Player> &Match::GetPlayers()
{
    return mPlayers;
}

Player &Match::GetCurrentPlayer()
{
    for (auto &player : mPlayers)
    {
        if (player.GetColor() == mPlayerCurrent)
        {
            return player;
        }
    }

    assert(false);
    return mPlayers[0];
}

void Match::SetCurrentPlayer(Player &player)
{
    mPlayerCurrent = player.GetColor();
}
} // namespace Server
