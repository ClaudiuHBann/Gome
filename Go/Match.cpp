#include "Go/pch.h"
//
#include "Match.h"
//

Match::Match(const vector<Player> &players) : mPlayers(players)
{
}

vector<Player> &Match::GetPlayers()
{
    return mPlayers;
}
