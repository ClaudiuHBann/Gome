#include "Go/pch.h"

#include "Game.h"

constexpr uint8_t CORNER_LEFT_UP = 218;
constexpr uint8_t CORNER_RIGHT_UP = 191;
constexpr uint8_t CORNER_LEFT_DOWN = 192;
constexpr uint8_t CORNER_RIGHT_DOWN = 217;

constexpr uint8_t PIECE_MIDDLE = 197;
constexpr uint8_t PIECE_VERTICAL = 179;
constexpr uint8_t PIECE_VERTICAL_LEFT = 195;
constexpr uint8_t PIECE_VERTICAL_RIGHT = 180;
constexpr uint8_t PIECE_HORIZONTAL = 196;
constexpr uint8_t PIECE_HORIZONTAL_DOWN = 193;
constexpr uint8_t PIECE_HORIZONTAL_UP = 194;

constexpr uint8_t STONE = 254;

namespace Client
{
GameI::GameI(const Coord &size)
    : mHandleConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE)), mKeylogger([&](const auto &key) {
          if (key == Keylogger::Key::ENTER)
          {
              AddStone();
          }
          else if (key == Keylogger::Key::F1 || key == Keylogger::Key::F2 || key == Keylogger::Key::F3)
          {
              UseJoker(key);
          }
          else
          {
              Move(key);
          }

          Draw();
      }),
      mBoard(size)
{
    Initialize();
}

void GameI::UseJoker(const Keylogger::Key /*key*/)
{
}

void GameI::AddStone()
{
}

void GameI::Initialize() const
{
    // set console code page to print extended ASCII chars
    SetConsoleOutputCP(437);

    // enable virtual terminal processing for console virtual terminal sequences
    // which we are going to use for changing the caret
    DWORD dwMode{};
    GetConsoleMode(mHandleConsoleOutput, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(mHandleConsoleOutput, dwMode);

    cout << "\x1b[1\x20q";
}

void GameI::Run()
{
    Draw();

    while (true)
    {
        mKeylogger.Check();
    }
}

void GameI::DrawBoard() const
{
    ResetCursor();

    DrawLineBorderTop();
    for (uint8_t row = 1; row < mBoard.GetGameState().size() - 1; row++)
    {
        DrawLineDivider(row);
    }
    DrawLineBorderBottom();
}

void GameI::DrawJokersState() const
{
    const auto &jokers = mPlayer.GetJokers();

    SetConsoleCursorPosition(mHandleConsoleOutput, {(SHORT)mBoard.GetGameState().front().size(), 1});
    cout << format("\t(F1) Joker Double-Move: {}", jokers[0] != Player::Joker::NONE ? "READY" : "USED");

    SetConsoleCursorPosition(mHandleConsoleOutput, {(SHORT)mBoard.GetGameState().front().size(), 2});
    cout << format("\t(F2) Joker Replace: {}", jokers[1] != Player::Joker::NONE ? "READY" : "USED");

    SetConsoleCursorPosition(mHandleConsoleOutput, {(SHORT)mBoard.GetGameState().front().size(), 3});
    cout << format("\t(F3) Joker Freedom: {}", jokers[2] != Player::Joker::NONE ? "READY" : "USED");
}

void GameI::Draw() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(mHandleConsoleOutput, &csbi);

    DrawBoard();
    DrawJokersState();

    SetConsoleCursorPosition(mHandleConsoleOutput, csbi.dwCursorPosition);
}

bool GameI::IsStoneOnPos(const Coord &pos) const
{
    return mBoard.GetGameState()[pos.GetXY().first][pos.GetXY().second] != Player::Color::NONE;
}

string GameI::GetStoneColored(const Coord &pos) const
{
    return format("\033[1;{}m{}\033[0m", to_string((int)mBoard.GetGameState()[pos.GetXY().first][pos.GetXY().second]),
                  (char)STONE);
}

string GameI::GetStoneColoredOr(const Coord &pos, const uint8_t value) const
{
    return IsStoneOnPos(pos) ? GetStoneColored(pos) : string(1, value);
}

void GameI::DrawLineDivider(const uint8_t row) const
{
    cout << GetStoneColoredOr({row, 0}, PIECE_VERTICAL_LEFT);
    for (uint8_t column = 1; column < mBoard.GetGameState().front().size() - 1; column++)
    {
        cout << PIECE_HORIZONTAL << GetStoneColoredOr({row, column}, PIECE_MIDDLE);
    }
    cout << PIECE_HORIZONTAL
         << GetStoneColoredOr({row, uint8_t(mBoard.GetGameState().front().size() - 1)}, PIECE_VERTICAL_RIGHT) << endl;
}

void GameI::DrawLineBorderTop() const
{
    cout << GetStoneColoredOr({0, 0}, CORNER_LEFT_UP);
    for (uint8_t column = 1; column < mBoard.GetGameState().front().size() - 1; column++)
    {
        cout << PIECE_HORIZONTAL << GetStoneColoredOr({0, column}, PIECE_HORIZONTAL_UP);
    }
    cout << PIECE_HORIZONTAL
         << GetStoneColoredOr({0, uint8_t(mBoard.GetGameState().front().size() - 1)}, CORNER_RIGHT_UP) << endl;
}

void GameI::DrawLineBorderBottom() const
{
    cout << GetStoneColoredOr({uint8_t(mBoard.GetGameState().size() - 1), 0}, CORNER_LEFT_DOWN);
    for (uint8_t column = 1; column < mBoard.GetGameState().front().size() - 1; column++)
    {
        cout << PIECE_HORIZONTAL
             << GetStoneColoredOr({uint8_t(mBoard.GetGameState().size() - 1), column}, PIECE_HORIZONTAL_DOWN);
    }
    cout << PIECE_HORIZONTAL
         << GetStoneColoredOr(
                {uint8_t(mBoard.GetGameState().size() - 1), uint8_t(mBoard.GetGameState().front().size() - 1)},
                CORNER_RIGHT_DOWN)
         << endl;
}

void GameI::ResetCursor() const
{
    SetConsoleCursorPosition(mHandleConsoleOutput, {});
}

bool GameI::IsPositionInBoardValid(const COORD &position) const
{
    return position.X >= 0 && position.X < mBoard.GetGameState().front().size() && position.Y >= 0 &&
           position.Y < mBoard.GetGameState().size();
}

COORD GameI::BoardToConsolePosition(const COORD &position) const
{
    return COORD(position.X * 2, position.Y);
}

void GameI::Move(const Keylogger::Key key)
{
    auto newPositionInBoard = mCurrentPositionInBoard;
    switch (key)
    {
    case Keylogger::Key::UP:
        newPositionInBoard.Y--;
        break;
    case Keylogger::Key::RIGHT:
        newPositionInBoard.X++;
        break;
    case Keylogger::Key::DOWN:
        newPositionInBoard.Y++;
        break;
    case Keylogger::Key::LEFT:
        newPositionInBoard.X--;
        break;
    }

    if (IsPositionInBoardValid(newPositionInBoard))
    {
        mCurrentPositionInBoard = move(newPositionInBoard);
        SetConsoleCursorPosition(mHandleConsoleOutput, BoardToConsolePosition(mCurrentPositionInBoard));
    }
}
} // namespace Client
