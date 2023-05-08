#pragma once

#include <queue>

// TODO: remove this Gome/pch.h dependency
#include "Gome/pch.h"

#include "Go/json.hpp"
using namespace nlohmann;

#include "Game/Board.h"
#include "Game/Player.h"

constexpr auto JSON_PLAYER_COLOR = "playerColor";
constexpr auto JSON_MATCH_RULES = "matchRules";

json JSONBoardAndMessageTo(const Game::Board &board, const string &message);
pair<Game::Board, string> JSONBoardAndMessageFrom(const string &jsonString);

json JSONStoneAndJokerTo(const Game::Stone &stone, const Game::Player::Joker joker);
pair<Game::Stone, Game::Player::Joker> JSONStoneAndJokerFrom(const string &jsonString);
