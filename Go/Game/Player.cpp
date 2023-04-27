#include "Go/pch.h"

#include "Player.h"
#include "Stone.h"

namespace Game
{
Player::Player(const Color color) : mColor(color)
{
}

Player::Color Player::GetColor() const
{
    return mColor;
}
}; // namespace Game
