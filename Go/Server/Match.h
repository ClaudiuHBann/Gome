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
    class Rules
    {
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rules, mPlayersPerMatch, mSize)

      public:
        Rules(const uint8_t playersPerMatch, const Coord &size);

        uint8_t GetPlayersPerMatch() const;
        const Coord &GetSize() const;

      private:
        uint8_t mPlayersPerMatch{};
        Coord mSize;
    };

    Match(Rules &rules);

    Player &GetPlayerCurrent();
    Player &GetPlayerNext();

  private:
    Rules &mRules;
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex{};

    Board mBoard;

    void CreateMatch(const Rules &rules);
};
} // namespace Server
