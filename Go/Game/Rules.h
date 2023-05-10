#pragma once

#include "Stone.h"

namespace Game
{
/**
 * @brief The rules of a match
 */
class Rules
{
  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rules, mPlayersPerMatch, mSize)

    /**
     * @brief Constructor
     */
    Rules();

    /**
     * @brief Constructor
     * @param playersPerMatch the number of players per match
     * @param size the size of the board
     */
    Rules(const uint8_t playersPerMatch, const Coord &size);

    /**
     * @brief Loads the rules from a file
     * @param file the file path
     * @return true if loaded successfully otherwise false
     */
    bool LoadFromFile(const string &file);

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
