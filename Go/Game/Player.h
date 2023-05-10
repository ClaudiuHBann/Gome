#pragma once

#include "Stone.h"

namespace Game
{
/**
 * @brief A match player
 */
class Player
{
  public:
    /**
     * @brief the possible colors a player
     */
    enum class Color : uint8_t
    {
        NONE = 37,
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        BLUE = 34,
        PURPLE = 35
    };

    /**
     * @brief The types of jokers a player can use
     */
    enum class Joker : uint8_t
    {
        NONE,
        DOUBLE_MOVE,
        REPLACE,
        FREEDOM
    };

    /**
     * @brief Constructor
     * @param color the color of the player
     */
    Player(const Color color);

    /**
     * @brief Gets the joker name
     * @param joker the joker
     * @return the name of the joker
     */
    static string GetJokerName(const Joker joker);

    /**
     * @brief Gets the name of a player's color
     * @param playerColor the player's color
     * @return the name of the player's color
     */
    static string GetColorName(const Player::Color playerColor);

    /**
     * @brief Tries to set an active joker for the player
     * @param joker the joker we try to activate
     * @return true if the joker was activated otherwise false
     */
    bool SetActiveJoker(const Joker joker);

    /**
     * @brief Gets the active joker of the player
     * @return the active joker of the player
     */
    Joker GetActiveJoker() const;

    /**
     * @brief Gets the jokers that the player has
     * @return the jokers that the player has
     */
    const vector<Joker> &GetJokers() const;

    /**
     * @brief Unvalidates the active joker
     */
    void UseActiveJoker();

    /**
     * @brief Gets the color of the player
     * @return the color of the player
     */
    Color GetColor() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const Player &) const = default;

  private:
    Color mColor = Color::NONE;
    Joker mJokerActive = Joker::NONE;
    vector<Joker> mJokers{Joker::DOUBLE_MOVE, Joker::REPLACE, Joker::FREEDOM};
};
}; // namespace Game
