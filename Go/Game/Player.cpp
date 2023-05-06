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

Player::Joker Player::GetActiveJoker() const
{
    return mJokerActive;
}

bool Player::SetActiveJoker(const Joker joker)
{
    auto itJoker = ranges::find(mJokers, joker);
    if (itJoker == mJokers.end())
    {
        return false;
    }

    mJokerActive = *itJoker;
    *itJoker = Joker::NONE;

    return true;
}

const vector<Player::Joker> &Player::GetJokers() const
{
    return mJokers;
}

void Player::UseActiveJoker()
{
    mJokerActive = Joker::NONE;
}
}; // namespace Game
