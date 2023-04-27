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
    Match(const vector<Player> &players, const Coord &size);

    Player &GetPlayerCurrent();
    Player &GetPlayerNext();
    size_t GetPlayerIndex() const;

  private:
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex{};

    Board mBoard;
};
} // namespace Server
