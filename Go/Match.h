#pragma once

#include "Player.h"

class Match
{
  public:
    Match(const vector<Player> &players) : mPlayers(players);

    vector<Player> &GetPlayers();

  private:
    vector<Player> mPlayers;
};
