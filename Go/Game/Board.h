#pragma once

#include "Player.h"

namespace Server
{
class Match;
}

namespace Game
{
/**
 * @brief Holds the game state of a match and implements the logic behind stone manipulation
 */
class Board
{
    friend class ::Server::Match;

  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Board, mGameState)

    /**
     * @brief Constructor
     * @param size the size of the board
     */
    Board(const Coord &size);

    /**
     * @brief Tries to add a stone in the board
     * @param player the player that wants to add the stone
     * @param stone the stone that the player wants to add
     * @param validate validates position
     * @return true if the operation was succeesful otherwise false
     */
    bool AddStone(Player &player, const Stone &stone, const bool validate = true);

    /**
     * @brief Checks if a player can place the stone
     * @param player the player that wants to add the stone
     * @param stone the stone that the player wants to add
     * @return true if the operation was succeesful otherwise false
     */
    bool IsStoneValid(const Player &player, const Stone &stone) const;

    /**
     * @brief Checks if a player can place any stone
     * @note checks joker moves too
     * @param player the player that we check for
     * @return tur if the player can place any stone otherwsise false
     */
    bool CanPlayerPlaceAnyStone(const Player &player) const;

    /**
     * @brief Checks if the game is in terminal state
     * @param players the players from the match
     * @return true if the game is finished otherwise false
     */
    bool IsGameStateTerminal(const vector<Player> &players) const;

    /**
     * @brief Checks if the position is valid
     * @note checks for the position in the board
     * @param pos the position that we check
     * @return true if the position is valid otherwise false
     */
    bool IsPositionValid(const Coord &pos) const;

    /**
     * @brief Checks if a stone is on the position
     * @param pos the position to check
     * @return true if stone is on pos otherwise false
     */
    bool IsStoneOnPos(const Coord &pos) const;

    /**
     * @brief Gets the color of the stone as a string
     * @param pos the position to get the color from
     * @return the stone's color as string
     */
    string GetStoneColorAsString(const Coord &pos) const;

    /**
     * @brief Gets the color of the stone if there is one else the passed value as string
     * @param pos the position to get the color of the stone from
     * @param value the value to be stigified if position is empty
     * @return the stone color or value as string
     */
    string GetStoneColorOrAsString(const Coord &pos, const uint8_t value) const;

    /**
     * @brief Gets the winner if there is one else nullopt
     * @param players the players of the match
     * @return the winner or nullopt
     */
    optional<Player::Color> GetWinner(const vector<Player> &players) const;

    /**
     * @brief Gets the size of the board
     * @return the size of the board
     */
    Coord GetSize() const;

    /**
     * @brief Gets the number of stones that the player places
     * @param player the player to look for
     * @return the stone count
     */
    uint8_t GetPlayerStoneCount(const Player &player) const;

    /**
     * @brief Gets a position from the game state
     * @return the position from the game state
     */
    Player::Color GetGameStatePos(const Coord &pos) const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const Board &) const = default;

  private:
    vector<vector<Player::Color>> mGameState{};

    /**
     * @brief Gets the numbers of stones (of the same color) around a position
     * @param player the player that we check for nearby stone
     * @param pos the position around we check
     * @return the number of stones
     */
    uint8_t GetSameStoneNearbyPosCount(const Player &player, const Coord &pos) const;

    /**
     * @brief Checks if there is at least a nearby stone as the same color
     * @param player the player that we check for
     * @param pos the position around we check
     * @return true if there is at least one stone of the same color around the position otherwise false
     */
    bool IsSameStoneNearbyPos(const Player &player, const Coord &pos) const;
};
}; // namespace Game
