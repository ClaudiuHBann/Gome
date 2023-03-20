#pragma once

#include "Stone.h"

class Table
{
  public:
    enum class Color
    {
        FG_Black = 30,
        FG_Red = 31,
        FG_Green = 32,
        FG_Blue = 34,
        FG_White = 37
    };

    Table(const size_t sizeRows, const size_t sizeColumns);

    void Draw();

  private:
    size_t mSizeRows{};
    size_t mSizeColumns{};

    void DrawStone(const Stone &stone, const Color color);
};
