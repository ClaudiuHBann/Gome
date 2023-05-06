#pragma once

#include "Go/Game/Board.h"
#include "Keylogger.h"

using namespace Game;

namespace Client
{
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
    Player mPlayer{Player::Color::NONE};

    bool IsStoneOnPos(const Coord &pos) const;
    string GetStoneColored(const Coord &pos) const;
    string GetStoneColoredOr(const Coord &pos, const uint8_t value) const;

    void Draw() const;
    void DrawBoard() const;
    void DrawJokersState() const;
    void DrawLineDivider(const uint8_t row) const;
    void DrawLineBorderTop() const;
    void DrawLineBorderBottom() const;

    void ResetCursor() const;
    bool IsPositionInBoardValid(const COORD &position) const;
    COORD BoardToConsolePosition(const COORD &position) const;

    void UseJoker(const Keylogger::Key key);
    void AddStone();
    void Move(const Keylogger::Key key);

    void Initialize() const;
};
} // namespace Client
