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

Player::Color Player::GetColor() const
{
    return mColor;
}
}; // namespace Game
