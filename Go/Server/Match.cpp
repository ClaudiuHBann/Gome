#include "Go/pch.h"

#include "Match.h"

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
    return mPlayers[mPlayerCurrentIndex];
}
} // namespace Server
