#pragma once

#include "Stone.h"

namespace Game
{
/**
 * @brief The rules of a match
 */
class Rules
{
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rules, mPlayersPerMatch, mSize)

  public:
    /**
     * @brief Constructor
     * @param playersPerMatch the number of players per match
     * @param size the size of the board
     */
    Rules(const uint8_t playersPerMatch, const Coord &size);

    /**
     * @brief Gets the number of players per match
     * @return the number of players per match
     */
    uint8_t GetPlayersPerMatch() const;

    /**
     * @brief Gets the size of the board
     * @return the size of the board
     */
    const Coord &GetSize() const;

  private:
    uint8_t mPlayersPerMatch{};
    Coord mSize;
};
} // namespace Game
