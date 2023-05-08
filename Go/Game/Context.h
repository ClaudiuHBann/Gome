#pragma once

#include "Rules.h"

namespace Game
{
// Context which will be send to the server
class ContextClient
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextClient, stone, joker)

    Stone stone;
    Player::Joker joker;
};

// Context which will be send to the client when a match starts
class ContextServerInit
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServerInit, rules, color)

    Rules rules;
    Player::Color color;
};

// Context which will be send to the client
class ContextServer
{
  public:
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ContextServer, board, message)

    Board board;
    string message;
};
} // namespace Game
