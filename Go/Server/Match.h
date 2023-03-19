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
    void SetCurrentPlayer(Player &player);

  private:
    vector<Player> mPlayers{};
    Player::Color mPlayerCurrent = Player::Color::NONE;
};
} // namespace Server
