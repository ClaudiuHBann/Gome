#pragma once

#include "Go/Game/Board.h"
#include "Keylogger.h"

using namespace Game;

class GameI
{
  public:
    GameI(const Coord &size);

    void Run();

  private:
    COORD mCurrentPositionInBoard{};
    HANDLE mHandleConsoleOutput{};
    Keylogger mKeylogger;
    Board mBoard;

    bool IsStoneOnPos(const Coord &pos) const;
    string GetStoneColored(const Coord &pos) const;
    string GetStoneColoredOr(const Coord &pos, const uint8_t value) const;

    void Draw();
    void DrawLineDivider(const uint8_t row) const;
    void DrawLineBorderTop() const;
    void DrawLineBorderBottom() const;

    void ResetCursor() const;
    bool IsPositionInBoardValid(const COORD &position) const;
    COORD BoardToConsolePosition(const COORD &position) const;
    void Move(const Keylogger::Key key);
};
