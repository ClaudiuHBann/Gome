#include "Go/pch.h"

#include "Board.h"
#include "Player.h"
#include "Stone.h"

namespace Game
{
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

Board::Board(const uint8_t sizeRows, const uint8_t sizeColumns)
    : mSizeRows(sizeRows), mSizeColumns(sizeColumns), mHandleConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE)),
      mGameState(sizeRows, vector<Player::Color>(sizeColumns, Player::Color::NONE))
{
}

void Board::AddStone(Stone &stone)
{
    auto &&pos = stone.GetPosition().GetXY();
    mGameState[pos.first][pos.second] = stone.GetPlayer().GetColor();
}

void Board::Draw()
{
    ResetCursor();

    DrawLineBorderTop();

    for (uint8_t row = 1; row < mSizeRows - 1; row++)
    {
        DrawLineDivider(row);
    }

    DrawLineBorderBottom();

    ResetCursor();
}

bool Board::IsStoneOnPos(const Coord &pos) const
{
    return mGameState[pos.GetXY().first][pos.GetXY().second] != Player::Color::NONE;
}

string Board::GetStoneColored(const Coord &pos) const
{
    return format("\033[1;{}m{}\033[0m", to_string((int)mGameState[pos.GetXY().first][pos.GetXY().second]),
                  (char)STONE);
}

string Board::GetStoneColoredOr(const Coord &pos, const uint8_t value) const
{
    return IsStoneOnPos(pos) ? GetStoneColored(pos) : string(1, value);
}

void Board::DrawLineDivider(const uint8_t row) const
{
    cout << GetStoneColoredOr({row, 0}, PIECE_VERTICAL_LEFT);
    for (uint8_t column = 1; column < mSizeColumns - 1; column++)
    {
        cout << PIECE_HORIZONTAL << GetStoneColoredOr({row, column}, PIECE_MIDDLE);
    }
    cout << PIECE_HORIZONTAL << GetStoneColoredOr({row, uint8_t(mSizeColumns - 1)}, PIECE_VERTICAL_RIGHT) << endl;
}

void Board::DrawLineBorderTop() const
{
    cout << GetStoneColoredOr({0, 0}, CORNER_LEFT_UP);
    for (uint8_t column = 1; column < mSizeColumns - 1; column++)
    {
        cout << PIECE_HORIZONTAL << GetStoneColoredOr({0, column}, PIECE_HORIZONTAL_UP);
    }
    cout << PIECE_HORIZONTAL << GetStoneColoredOr({0, uint8_t(mSizeColumns - 1)}, CORNER_RIGHT_UP) << endl;
}

void Board::DrawLineBorderBottom() const
{
    cout << GetStoneColoredOr({uint8_t(mSizeRows - 1), 0}, CORNER_LEFT_DOWN);
    for (uint8_t column = 1; column < mSizeColumns - 1; column++)
    {
        cout << PIECE_HORIZONTAL << GetStoneColoredOr({uint8_t(mSizeRows - 1), column}, PIECE_HORIZONTAL_DOWN);
    }
    cout << PIECE_HORIZONTAL
         << GetStoneColoredOr({uint8_t(mSizeRows - 1), uint8_t(mSizeColumns - 1)}, CORNER_RIGHT_DOWN) << endl;
}

void Board::ResetCursor() const
{
    SetConsoleCursorPosition(mHandleConsoleOutput, {});
}
}; // namespace Game
