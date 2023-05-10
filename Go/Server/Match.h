#pragma once

#include "Go/Game/Board.h"
#include "Go/Game/Player.h"
#include "Go/Game/Rules.h"

namespace Server
{
using namespace Game;

/**
 * @brief Match context
 */
class Match
{
    friend class MatchManager;

  public:
    /**
     * @brief Constructor
     * @param rules the rules of the match
     */
    Match(Rules &rules);

    /**
     * @brief Gets the current player
     * @return the current player
     */
    Player &GetPlayerCurrent();

    /**
     * @brief Cycles the players
     * @return the next player
     */
    Player &GetPlayerNext();

  private:
    Rules &mRules;
    vector<Player> mPlayers{};
    size_t mPlayerCurrentIndex{};

    Board mBoard;

    /**
     * @brief Creates a match with the specified rules
     * @param rules the rules of the match
     */
    void CreateMatch(const Rules &rules);
};
} // namespace Server
