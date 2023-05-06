#pragma once

#include "Stone.h"

namespace Game
{
class Player
{
  public:
    enum class Color : uint8_t
    {
        NONE = 37,
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        BLUE = 34,
        PURPLE = 35
    };

    enum class Joker : uint8_t
    {
        NONE,
        DOUBLE_MOVE,
        REPLACE,
        FREEDOM
    };

    Player(const Color color);

    bool SetActiveJoker(const Joker joker);
    Joker GetActiveJoker() const;
    void UseActiveJoker();

    Color GetColor() const;

  private:
    Color mColor = Color::NONE;
    Joker mJokerActive = Joker::NONE;
    vector<Joker> mJokers{Joker::DOUBLE_MOVE, Joker::REPLACE, Joker::FREEDOM};
};
}; // namespace Game
