#include "Go/pch.h"

#include "Rules.h"

namespace Game
{
Rules::Rules(const uint8_t playersPerMatch, const Coord &size) : mPlayersPerMatch(playersPerMatch), mSize(size)
{
}

uint8_t Rules::GetPlayersPerMatch() const
{
    return mPlayersPerMatch;
}

const Coord &Rules::GetSize() const
{
    return mSize;
}
} // namespace Game
