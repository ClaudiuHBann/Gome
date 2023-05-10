#include "Go/pch.h"

#include "Board.h"
#include "Player.h"
#include "Stone.h"

namespace Game
{
constexpr auto MAX_NEARBY_STONES_COUNT = 8ui8;

Board::Board(const Coord &size)
    : mGameState(size.GetXY().first, vector<Player::Color>(size.GetXY().second, Player::Color::NONE))
{
}

bool Board::AddStone(Player &player, const Stone &stone)
{
    if (!IsStoneValid(player, stone))
    {
        return false;
    }

    if (player.GetActiveJoker() != Player::Joker::DOUBLE_MOVE)
    {
        player.UseActiveJoker();
    }

    auto &&pos = stone.GetPosition().GetXY();
    mGameState[pos.first][pos.second] = player.GetColor();
    return true;
}

uint8_t Board::GetSameStoneNearbyPosCount(const Player &player, const Coord &poss) const
{
    auto &&pos = poss.GetXY();
    auto playerColor = player.GetColor();

    uint8_t count{};

    auto GetPlayerColorFromStonePos = [this](const Coord &pos) {
        if (!IsPositionValid(pos))
        {
            return Player::Color::NONE;
        }

        return mGameState[pos.GetXY().first][pos.GetXY().second];
    };

    // TODO: is there a better solution for doing this?
    if (GetPlayerColorFromStonePos({uint8_t(pos.first - 1), pos.second}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(pos.first - 1), uint8_t(pos.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({pos.first, uint8_t(pos.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(pos.first + 1), uint8_t(pos.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(pos.first + 1), pos.second}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(pos.first + 1), uint8_t(pos.second - 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({pos.first, uint8_t(pos.second - 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(pos.first - 1), uint8_t(pos.second - 1)}) == playerColor)
    {
        count++;
    }

    return count;
}

bool Board::IsSameStoneNearbyPos(const Player &player, const Coord &poss) const
{
    return GetSameStoneNearbyPosCount(player, poss);
}

bool Board::IsPositionValid(const Coord &poss) const
{
    auto &&pos = poss.GetXY();
    return pos.first >= 0 && pos.first < mGameState.front().size() && pos.second >= 0 && pos.second < mGameState.size();
}

bool Board::IsStoneValid(const Player &player, const Stone &stone) const
{
    auto &&pos = stone.GetPosition().GetXY();
    if (!IsPositionValid(stone.GetPosition()))
    {
        return false;
    }

    auto joker = player.GetActiveJoker();
    switch (joker)
    {
    case Player::Joker::REPLACE:
        return IsSameStoneNearbyPos(player, stone.GetPosition());
    case Player::Joker::FREEDOM:
        return mGameState[pos.first][pos.second] == Player::Color::NONE;
    }

    return mGameState[pos.first][pos.second] == Player::Color::NONE &&
           IsSameStoneNearbyPos(player, stone.GetPosition());
}

const vector<vector<Player::Color>> &Board::GetGameState() const
{
    return mGameState;
}

bool Board::CanPlayerPlaceAnyStone(const Player &player) const
{
    for (uint8_t row = 0; row < mGameState.size(); row++)
    {
        for (uint8_t column = 0; column < mGameState.front().size(); column++)
        {
            for (const auto &joker : player.GetJokers())
            {
                switch (joker)
                {
                // we can place on a free spot without nearby allies
                case Player::Joker::FREEDOM: {
                    if (mGameState[row][column] == Player::Color::NONE)
                    {
                        return true;
                    }
                }
                break;

                // we can place anywhere but need to have nearby allies
                case Player::Joker::REPLACE: {
                    if (GetSameStoneNearbyPosCount(player, {row, column}) < MAX_NEARBY_STONES_COUNT)
                    {
                        return true;
                    }
                }
                break;

                // DOUBLE_MOVE is the same as a joker free move and
                default: {
                    if (mGameState[row][column] == Player::Color::NONE &&
                        GetSameStoneNearbyPosCount(player, {row, column}) < MAX_NEARBY_STONES_COUNT)
                    {
                        return true;
                    }
                }
                break;
                }
            }
        }
    }

    return false;
}

bool Board::IsGameStateTerminal(const vector<Player> &players) const
{
    for (auto &player : players)
    {
        if (CanPlayerPlaceAnyStone(player))
        {
            return false;
        }
    }

    return true;
}

optional<Player::Color> Board::GetWinner(const vector<Player> &players) const
{
    if (!IsGameStateTerminal(players))
    {
        return nullopt;
    }

    uint8_t playerBestIndex = 0;
    uint8_t playerBestStoneCount = 0;
    for (uint8_t i = 0; i < players.size(); i++)
    {
        uint8_t playerStoneCount = 0;
        for (const auto &row : mGameState)
        {
            for (const auto &column : row)
            {
                if (players[i].GetColor() == column)
                {
                    playerStoneCount++;
                }
            }
        }

        if (playerStoneCount >= playerBestStoneCount)
        {
            playerBestIndex = i;
        }
    }

    return players[playerBestIndex].GetColor();
}
}; // namespace Game
