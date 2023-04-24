#include "Go/pch.h"

#include "Player.h"
#include "Table.h"

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

Board::Board(const size_t sizeRows, const size_t sizeColumns)
    : mSizeRows(sizeRows), mSizeColumns(sizeColumns), mHandleConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

void Board::Draw()
{
    ResetCursor();

    DrawLineBorderTop();

    for (size_t row = 1; row < mSizeRows; row++)
    {
        DrawLine(uint8_t(row - 1));
        DrawLineDivider();
    }

    DrawLine(uint8_t(mSizeRows - 1));
    DrawLineBorderBottom();

    ResetCursor();
}

void Board::DrawLine(const uint8_t /*row*/) const
{
    for (size_t column = 0; column < mSizeColumns; column++)
    {
        cout << PIECE_VERTICAL << /*mGameState.board[row][column]*/ ' ';
    }
    cout << PIECE_VERTICAL << endl;
}

void Board::DrawLineDivider() const
{
    cout << PIECE_VERTICAL_LEFT;
    for (size_t column = 1; column < mSizeColumns; column++)
    {
        cout << PIECE_HORIZONTAL << PIECE_MIDDLE;
    }
    cout << PIECE_HORIZONTAL << PIECE_VERTICAL_RIGHT << endl;
}

void Board::DrawLineBorderTop() const
{
    cout << CORNER_LEFT_UP;
    for (size_t column = 1; column < mSizeColumns; column++)
    {
        cout << PIECE_HORIZONTAL << PIECE_HORIZONTAL_UP;
    }
    cout << PIECE_HORIZONTAL << CORNER_RIGHT_UP << endl;
}

void Board::DrawLineBorderBottom() const
{
    cout << CORNER_LEFT_DOWN;
    for (size_t column = 1; column < mSizeColumns; column++)
    {
        cout << PIECE_HORIZONTAL << PIECE_HORIZONTAL_DOWN;
    }
    cout << PIECE_HORIZONTAL << CORNER_RIGHT_DOWN << endl;
}

void Board::ResetCursor() const
{
    SetConsoleCursorPosition(mHandleConsoleOutput, {});
}
}; // namespace Game
