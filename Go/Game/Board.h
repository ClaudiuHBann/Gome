#pragma once

#include "Player.h"

namespace Game
{
class Board
{
  public:
    enum class Color
    {
        FG_White = 37,
        FG_Black = 30,
        FG_Red = 31,
        FG_Green = 32,
        FG_Blue = 34,
        FG_Purple = 35
    };

    Board(const uint8_t sizeRows, const uint8_t sizeColumns);

    void Draw();

    void AddStone(Stone &stone);

  private:
    uint8_t mSizeRows{};
    uint8_t mSizeColumns{};
    HANDLE mHandleConsoleOutput{};

    vector<vector<Player::Color>> mGameState{};

    bool IsStoneOnPos(const Coord &pos) const;
    string GetStoneColored(const Coord &pos) const;
    string GetStoneColoredOr(const Coord &pos, const uint8_t value) const;

    void DrawLineDivider(const uint8_t row) const;
    void DrawLineBorderTop() const;
    void DrawLineBorderBottom() const;

    void ResetCursor() const;
};
}; // namespace Game
