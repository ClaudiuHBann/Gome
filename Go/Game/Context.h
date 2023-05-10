#pragma once

#include "Board.h"
#include "Rules.h"

namespace Game
{
/**
 * @brief Interface for contexts
 */
class IContext
{
  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(IContext, mType)

    /**
     * @brief Types of context
     */
    enum class Type
    {
        NONE = 1, // if this is 0 then we need to change the json (de)serializing methods
        CLIENT,
        SERVER_INIT,
        SERVER,
        SERVER_UNINIT
    };

    /**
     * @brief Gets the type of the context
     * @return the type of the context
     */
    Type GetType() const;

    /**
     * @brief Creates the json from the derived context
     * @return the json from the derived context
     */
    string ToJSONString() const;

    /**
     * @brief Creates the derived context from the json
     * @param json the context json
     */
    void FromJSONString(const string &jsonString);

  protected:
    /**
     * @brief Constructor
     * @param type the type of context
     */
    IContext(const Type type);

  private:
    Type mType = Type::NONE;
};

/**
 * @brief Context which will be send to the server
 */
class ContextClient : public IContext
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextClient, stone, joker)

    Stone stone;
    Player::Joker joker;

    /**
     * @brief Constructor
     * @param stone the stone that tries to be placed
     * @param joker the joker that the player is using
     */
    ContextClient(const Stone &stone, const Player::Joker joker);
};

/**
 * @brief Context which will be send to the client when a match starts
 */
class ContextServerInit : public IContext
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServerInit, rules, color)

    Rules rules;
    Player::Color color;

    /**
     * @brief Constructor
     * @param rules the rules of the match
     * @param color the color of the player that receives this context
     */
    ContextServerInit(const Rules &rules, const Player::Color color);
};

class ContextServerUninit : public IContext
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServerUninit, winner)

    Player::Color winner;

    /**
     * @brief Constructor
     * @param winner the winner of the game
     */
    ContextServerUninit(const Player::Color winner);
};

/**
 * @brief Context which will be send to the client
 */
class ContextServer : public IContext
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServer, board, message)

    Board board;
    string message;

    /**
     * @brief Construcotr
     * @param board the game state
     * @param message an informative message
     */
    ContextServer(const Board &board, const string &message);
};
} // namespace Game
