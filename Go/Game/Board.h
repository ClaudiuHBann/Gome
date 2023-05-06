#pragma once

#include "Player.h"

namespace Game
{
class Board
{
  public:
    Board(const Coord &size);

    void AddStone(Player &player, const Stone &stone);

    bool IsStoneValid(const Player &player, const Stone &stone) const;
    bool CanPlayerPlaceAnyStone(const Player &player) const;
    bool IsGameStateTerminal(const vector<Player> &players) const;

    optional<Player::Color> GetWinner(const vector<Player> &players) const;
    const vector<vector<Player::Color>> &GetGameState() const;

  private:
    vector<vector<Player::Color>> mGameState{};

    // gets the numbers of stones (the same color) around a position
    uint8_t GetSameStoneNearbyPosCount(const Player &player, const Coord &pos) const;

    // returns true if there is at least one stone (the same color)
    // around that position else returns false
    bool IsSameStoneNearbyPos(const Player &player, const Coord &pos) const;
};
}; // namespace Game
