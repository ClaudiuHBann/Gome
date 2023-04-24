#include "Go/pch.h"

#include "Player.h"
#include "Stone.h"

namespace Game
{
Player::Player(const Color color) : mColor(color)
{
}

void Player::StoneAdd(const Stone &stone)
{
    mStones.push_back(stone);
}

void Player::StoneMove(const Stone &stone, const Coord &pos)
{
    auto it = find(mStones.begin(), mStones.end(), stone);
    if (it != mStones.end())
    {
        it->SetPosition(pos);
    }
}

Player::Color Player::GetColor() const
{
    return mColor;
}
}; // namespace Game
