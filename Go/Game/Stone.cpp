#include "Go/pch.h"

#include "Player.h"
#include "Stone.h"

namespace Game
{
Coord::Coord(const uint8_t x, const uint8_t y) : mX(x), mY(y)
{
}

pair<uint8_t, uint8_t> Coord::GetXY() const
{
    return {mX, mY};
}

Stone::Stone(const Coord &pos) : mPosition(pos)
{
}

const Coord &Stone::GetPosition() const
{
    return mPosition;
}
}; // namespace Game
