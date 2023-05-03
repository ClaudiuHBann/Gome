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

    bool IsStoneValid(Stone &stone) const;
    bool CanPlayerPlaceAnyStone(Player &player) const;
    bool IsGameStateTerminal(vector<Player> &players) const;

    optional<Player::Color> GetWinner(vector<Player> &players) const;

  private:
    vector<vector<Player::Color>> mGameState{};

    // gets the numbers of stones (the same color) around a position
    uint8_t GetSameStoneNearbyPosCount(Stone &stone, const Coord &pos) const;
    // returns true if there is at least one stone (the same color)
    // around that position else returns false
    bool IsSameStoneNearbyPos(Stone &stone, const Coord &pos) const;
};
}; // namespace Game
