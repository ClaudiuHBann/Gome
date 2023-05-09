#pragma once

#include "Board.h"
#include "Rules.h"

namespace Game
{
/**
 * @brief Context which will be send to the server
 */
class ContextClient
{
  public:
    inline void to_json(nlohmann::json &j, const ContextClient &context)
    {
        j["stone"] = context.stone;
        j["joker"] = (uint16_t)context.joker;
    }

    inline void from_json(const nlohmann::json &j, ContextClient &context)
    {
        uint16_t jokerr{};
        j.at("stone").get_to(context.stone);
        j.at("joker").get_to(jokerr);
        context.joker = (Player::Joker)jokerr;
    }

    Stone stone;
    Player::Joker joker;

    ContextClient(const Stone &stone, const Player::Joker joker);
};

/**
 * @brief Context which will be send to the client when a match starts
 */
class ContextServerInit
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServerInit, rules, color)

    Rules rules;
    Player::Color color;

    ContextServerInit(const Rules &rules, const Player::Color color);
};

/**
 * @brief Context which will be send to the client
 */
class ContextServer
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServer, board, message)

    Board board;
    string message;

    ContextServer(const Board &board, const string &message);
};
} // namespace Game
