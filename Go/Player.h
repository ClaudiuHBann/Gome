#pragma once

#include "Stone.h"

class Player
{
  public:
    enum class Color
    {
        BLACK,
        RED,
        GREEN,
        BLUE,
        WHITE
    };

    Player(const Color color);

    void AddStone(const Stone &stone);
    void RemoveStone(const Stone &stone);

    Color GetColor();

  private:
    Color mColor{};
    vector<Stone> mStones{};
};
