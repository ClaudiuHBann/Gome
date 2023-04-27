#pragma once

#include "Player.h"

namespace Game
{
class Board
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

    Board(const size_t sizeRows, const size_t sizeColumns);

    void Draw();

    void AddStone(Stone &stone);

  private:
    size_t mSizeRows{};
    size_t mSizeColumns{};
    HANDLE mHandleConsoleOutput{};

    vector<vector<Player::Color>> mGameState{};

    void DrawLine(const uint8_t row) const;
    void DrawLineDivider() const;
    void DrawLineBorderTop() const;
    void DrawLineBorderBottom() const;

    void ResetCursor() const;
};
}; // namespace Game
