#pragma once

#include "Go/Game/Board.h"
#include "Go/Game/Player.h"

namespace Server
{
using namespace Game;

class Match
{
    friend class MatchManager;

  public:
    Match(const uint8_t playersPerMatch, const Coord &size);

    Player &GetPlayerCurrent();
    Player &GetPlayerNext();

  private:
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex{};

    Board mBoard;

    void CreateMatch(const uint8_t playersPerMatch, const Coord &size);
};
} // namespace Server
