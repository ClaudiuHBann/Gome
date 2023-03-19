#include "Go/pch.h"
//
#include "Stone.h"
//

Stone::Stone(const size_t x, const size_t y) : mX(x), mY(y)
{
}

pair<size_t, size_t> Stone::GetPosition() const
{
    return {mX, mY};
}

void Stone::SetPosition(const size_t x, const size_t y)
{
    mX = x;
    mY = y;
}

bool Stone::operator==(const Stone &stone)
{
    auto &&pos = stone.GetPosition();

    return mX == pos.first && mY == pos.second;
}
