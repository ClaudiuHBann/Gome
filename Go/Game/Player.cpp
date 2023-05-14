#include "Go/pch.h"

#include "Player.h"
#include "Stone.h"

namespace Game
{
Player::Player(const Color color, const vector<pair<Player::Joker, bool>> &jokers /* = {} */)
    : mColor(color), mJokers(jokers)
{
}

Player::Color Player::GetColor() const
{
    return mColor;
}

/* static */ string Player::GetColorName(const Player::Color playerColor)
{
    switch (playerColor)
    {
    case Color::NONE:
        return "NONE"s;
    case Color::BLACK:
        return "BLACK"s;
    case Color::RED:
        return "RED"s;
    case Color::GREEN:
        return "GREEN"s;
    case Color::BLUE:
        return "BLUE"s;
    case Color::PURPLE:
        return "PURPLE"s;
    default:
        return "UNKNOWN"s;
    }
}

Player::Joker Player::GetActiveJoker() const
{
    return mJokerActive;
}

/* static */ string Player::GetJokerName(const Joker joker)
{
    switch (joker)
    {
    case Joker::NONE:
        return "NONE"s;
    case Joker::DOUBLE_MOVE:
        return "DOUBLE_MOVE"s;
    case Joker::REPLACE:
        return "REPLACE"s;
    case Joker::FREEDOM:
        return "FREEDOM"s;
    default:
        return "UNKNOWN"s;
    }
}

void Player::DeactivateActiveJoker()
{
    if (mJokerActive == Joker::NONE)
    {
        return;
    }

    ranges::find_if(mJokers, [&](const auto &pair) { return pair.first == mJokerActive; })->second = true;
    mJokerActive = Joker::NONE;
}

bool Player::SetActiveJoker(const Joker joker)
{
    // signal to deactivate current active joker if there is one
    if (joker == Joker::NONE)
    {
        DeactivateActiveJoker();
        return true;
    }

    // already used
    auto it = ranges::find_if(mJokers, [&](const auto &pair) { return pair.first == joker; });
    if (!it->second)
    {
        return false;
    }

    // save previous active joker if there is one
    DeactivateActiveJoker();

    it->second = false;
    mJokerActive = it->first;

    return true;
}

const vector<pair<Player::Joker, bool>> &Player::GetJokers() const
{
    return mJokers;
}

void Player::UseActiveJoker()
{
    if (mJokerActive == Joker::NONE)
    {
        return;
    }

    ranges::find_if(mJokers, [&](const auto &pair) { return pair.first == mJokerActive; })->second = false;
    mJokerActive = Joker::NONE;
}
}; // namespace Game
