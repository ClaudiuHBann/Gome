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
    enum class Type : uint8_t
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
    // nlohmann json cpp macros doesn't work with inheritance so we create them
    void to_json(nlohmann::json &nlohmann_json_j, const ContextClient &nlohmann_json_t);
    void from_json(const nlohmann::json &nlohmann_json_j, ContextClient &nlohmann_json_t);

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
    // nlohmann json cpp macros don't work with inheritance so we create them
    void to_json(nlohmann::json &nlohmann_json_j, const ContextServerInit &nlohmann_json_t);
    void from_json(const nlohmann::json &nlohmann_json_j, ContextServerInit &nlohmann_json_t);

    Rules rules;
    Player::Color color;

    /**
     * @brief Constructor
     * @param rules the rules of the match
     * @param color the color of the player that receives this context
     */
    ContextServerInit(const Rules &rules, const Player::Color color);
};

/**
 * @brief Context which will be send to the client whe match ends
 */
class ContextServerUninit : public IContext
{
  public:
    // nlohmann json cpp macros don't work with inheritance so we create them
    void to_json(nlohmann::json &nlohmann_json_j, const ContextServerUninit &nlohmann_json_t);
    void from_json(const nlohmann::json &nlohmann_json_j, ContextServerUninit &nlohmann_json_t);

    Player::Color winner;
    string message;

    /**
     * @brief Constructor
     * @param winner the winner of the game
     * @param message a message containing the final game state
     */
    ContextServerUninit(const Player::Color winner, const string &message);
};

/**
 * @brief Context which will be send to the client
 */
class ContextServer : public IContext
{
  public:
    // nlohmann json cpp macros don't work with inheritance so we create them
    void to_json(nlohmann::json &nlohmann_json_j, const ContextServer &nlohmann_json_t);
    void from_json(const nlohmann::json &nlohmann_json_j, ContextServer &nlohmann_json_t);

    /**
     * @brief The type of errors that a player can do
     */
    enum class Error : uint8_t
    {
        NONE = 1, // if this is 0 then we need to change the json (de)serializing methods
        WAIT,     // not all the players connected to the server
        TURN,     // not the turn of the requesting player
        JOKER,    // joker already used
        STONE     // could not add stone
    };

    Board board;
    vector<pair<Player::Joker, bool>> jokers;
    Error error;
    string message;

    /**
     * @brief Construcotr
     * @param board the game state
     * @param message an informative message
     */
    ContextServer(const Board &board, const vector<pair<Player::Joker, bool>> &jokers, const Error error,
                  const string &message);
};
} // namespace Game
