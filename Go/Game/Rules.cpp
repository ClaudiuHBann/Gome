#include "Go/pch.h"

#include "Rules.h"

namespace Game
{
Rules::Rules() : mSize(0, 0)
{
}

Rules::Rules(const uint8_t playersPerMatch, const Coord &size) : mPlayersPerMatch(playersPerMatch), mSize(size)
{
}

bool Rules::LoadFromFile(const string &file)
{
    ifstream stream(file);
    if (!stream.is_open())
    {
        return false;
    }

    from_json(json::parse(stream), *this);
    return true;
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
