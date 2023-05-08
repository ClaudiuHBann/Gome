#pragma once

#include "Go/Game/Board.h"
#include "Keylogger.h"

using namespace Game;

namespace Client
{
class GameI
{
  public:
    GameI();

    void Run();

  private:
    COORD mCurrentPositionInBoard{};
    HANDLE mHandleConsoleOutput{};
    Keylogger mKeylogger;

    Board mBoard{Coord{0, 0}};
    deque<string> mMessages{"Message: 1"s, "Message: 2"s, "Message: 3"s, "Message: 4"s, "Message: 5"s};

    Player mPlayer{Player::Color::NONE};

    bool IsStoneOnPos(const Coord &pos) const;
    string GetStoneColored(const Coord &pos) const;
    string GetStoneColoredOr(const Coord &pos, const uint8_t value) const;

    void Draw() const;
    void DrawBoard() const;
    void DrawJokersState() const;
    void DrawMessages() const;
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
