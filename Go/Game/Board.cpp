#include "Go/pch.h"

#include "Board.h"
#include "Player.h"
#include "Stone.h"

namespace Game
{
Board::Board(const uint8_t sizeRows, const uint8_t sizeColumns)
    : mGameState(sizeRows, vector<Player::Color>(sizeColumns, Player::Color::NONE))
{
}

void Board::AddStone(Stone &stone)
{
    auto &&pos = stone.GetPosition().GetXY();
    mGameState[pos.first][pos.second] = stone.GetPlayer().GetColor();
}
}; // namespace Game
