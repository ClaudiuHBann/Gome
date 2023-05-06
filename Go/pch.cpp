#include "pch.h"

using namespace Game;

constexpr auto JSON_BOARD_MESSAGE = "message";
constexpr auto JSON_STONE_JOKER = "joker";

json JSONBoardAndMessageTo(const Board &board, const string &message)
{
    json j;
    to_json(j, board);
    j[JSON_BOARD_MESSAGE] = message;

    return j;
}

pair<Board, string> JSONBoardAndMessageFrom(const string &jsonString)
{
    auto &&json = json::parse(jsonString);

    string message = json.at(JSON_BOARD_MESSAGE);
    json.erase(JSON_BOARD_MESSAGE);

    Board board({0, 0});
    from_json(json, board);

    return {board, message};
}

json JSONStoneAndJokerTo(const Stone &stone, const Player::Joker joker)
{
    json j;
    to_json(j, stone);
    j[JSON_STONE_JOKER] = joker;

    return j;
}

pair<Stone, Player::Joker> JSONStoneAndJokerFrom(const string &jsonString)
{
    auto &&json = json::parse(jsonString);

    Player::Joker joker = json.at(JSON_STONE_JOKER);
    json.erase(JSON_STONE_JOKER);

    Stone stone({0, 0});
    from_json(json, stone);

    return {stone, joker};
}
