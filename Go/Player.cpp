#include "Go/pch.h"
//
#include "Player.h"
//

Player::Player(Client &&client, const Color color) : mClient(client), mColor(color)
{
}

void Player::AddStone(const Stone &stone)
{
    mStones.push_back(stone);
}

void Player::RemoveStone(const Stone &stone)
{
    for (auto it = mStones.begin(); it != mStones.end(); it++)
    {
        if (*it == stone)
        {
            mStones.erase(it);
            break;
        }
    }
}

Player::Color Player::GetColor()
{
    return mColor;
}
