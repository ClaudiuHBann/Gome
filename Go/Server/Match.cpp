#include "Go/pch.h"

#include "Go/Game/Stone.h"
#include "Match.h"

namespace Server
{
Match::Match(const vector<Player> &players, const Coord &size)
    : mPlayers(players), mBoard(size.GetXY().first, size.GetXY().second)
{
}

Player &Match::GetPlayerCurrent()
{
    return mPlayers[mPlayerCurrentIndex];
}

Player &Match::GetPlayerNext()
{
    mPlayerCurrentIndex = (mPlayerCurrentIndex + 1) % mPlayers.size();
    return GetPlayerCurrent();
}

size_t Match::GetPlayerIndex() const
{
    return mPlayerCurrentIndex;
}
} // namespace Server
