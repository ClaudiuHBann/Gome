#pragma once

#include "Player.h"

class GameI;

namespace Game
{
class Board
{
    friend class GameI;

  public:
    Board(const uint8_t sizeRows, const uint8_t sizeColumns);

    void AddStone(Stone &stone);

  private:
    vector<vector<Player::Color>> mGameState{};
};
}; // namespace Game
