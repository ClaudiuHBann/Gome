#include "Go/pch.h"

#include "Context.h"

namespace Game
{
ContextClient::ContextClient(const Stone &stone, const Player::Joker joker) : stone(stone), joker(joker)
{
}

ContextServerInit::ContextServerInit(const Rules &rules, const Player::Color color) : rules(rules), color(color)
{
}

ContextServer::ContextServer(const Board &board, const string &message) : board(board), message(message)
{
}
} // namespace Game
