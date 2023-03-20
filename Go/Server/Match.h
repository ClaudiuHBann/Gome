#pragma once

#include "Go/Player.h"

namespace Server
{
class Match
{
  public:
    void AddPlayer(const Player &player);

    vector<Player> &GetPlayers();
    Player &GetCurrentPlayer();

  private:
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex = 0;
};
} // namespace Server
