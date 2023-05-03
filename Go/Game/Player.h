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

    Player(const Color color);

    Color GetColor() const;

  private:
    Color mColor = Color::NONE;
    vector<Stone> mStones{};
};
}; // namespace Game
