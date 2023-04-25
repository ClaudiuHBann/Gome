#pragma once

#include "Go/Game/Player.h"

namespace Server
{
using namespace Game;

class Match
{
  public:
    void AddPlayer(const Player &player);

    vector<Player> &GetPlayers();
    Player &GetCurrentPlayer();

  private:
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex{};
};
} // namespace Server
