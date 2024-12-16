#include "Go/pch.h"

#include "Board.h"
#include "Player.h"
#include "Stone.h"

namespace Game
{
constexpr auto MAX_NEARBY_STONES_COUNT = 8ui8;
constexpr auto STONE = 254ui8;

Board::Board(const Coord &size)
    : mGameState(size.GetXY().first, vector<Player::Color>(size.GetXY().second, Player::Color::NONE))
{
}

bool Board::AddStone(Player &player, const Stone &stone, const bool validate /* = true */)
{
    if (validate && !IsStoneValid(player, stone))
    {
        player.DeactivateActiveJoker();
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

uint8_t Board::GetSameStoneNearbyPosCount(const Player &player, const Coord &pos) const
{
    auto &&posXY = pos.GetXY();
    auto playerColor = player.GetColor();

    uint8_t count{};

    auto GetPlayerColorFromStonePos = [this](const Coord &pos) {
        if (!IsPositionValid(pos))
        {
            return Player::Color::UNKNOWN;
        }

        return GetGameStatePos(pos);
    };

    // TODO: is there a better solution for doing this?
    if (GetPlayerColorFromStonePos({uint8_t(posXY.first - 1), posXY.second}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(posXY.first - 1), uint8_t(posXY.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({posXY.first, uint8_t(posXY.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(posXY.first + 1), uint8_t(posXY.second + 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(posXY.first + 1), posXY.second}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(posXY.first + 1), uint8_t(posXY.second - 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({posXY.first, uint8_t(posXY.second - 1)}) == playerColor)
    {
        count++;
    }

    if (GetPlayerColorFromStonePos({uint8_t(posXY.first - 1), uint8_t(posXY.second - 1)}) == playerColor)
    {
        count++;
    }

    return count;
}

bool Board::IsSameStoneNearbyPos(const Player &player, const Coord &pos) const
{
    return GetSameStoneNearbyPosCount(player, pos);
}

bool Board::IsPositionValid(const Coord &pos) const
{
    auto &&posXY = pos.GetXY();
    return posXY.first >= 0 && posXY.first < GetSize().GetXY().first && posXY.second >= 0 &&
           posXY.second < GetSize().GetXY().second;
}

bool Board::IsStoneOnPos(const Coord &pos) const
{
    return GetGameStatePos(pos) != Player::Color::NONE;
}

string Board::GetStoneColorAsString(const Coord &pos) const
{
    return format("\033[1;{}m{}\033[0m", to_string((int)GetGameStatePos(pos)), (char)STONE);
}

string Board::GetStoneColorOrAsString(const Coord &pos, const uint8_t value) const
{
    return IsStoneOnPos(pos) ? GetStoneColorAsString(pos) : string(1, value);
}

bool Board::IsStoneValid(const Player &player, const Stone &stone) const
{
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
        return GetGameStatePos(stone.GetPosition()) == Player::Color::NONE;
    }

    return GetGameStatePos(stone.GetPosition()) == Player::Color::NONE &&
           IsSameStoneNearbyPos(player, stone.GetPosition());
}

Player::Color Board::GetGameStatePos(const Coord &pos) const
{
    auto &&posXY = pos.GetXY();
    return mGameState[posXY.first][posXY.second];
}

uint8_t Board::GetPlayerStoneCount(const Player &player) const
{
    uint8_t stoneCount{};

    for (uint8_t row = 0; row < GetSize().GetXY().first; row++)
    {
        for (uint8_t column = 0; column < GetSize().GetXY().second; column++)
        {
            if (mGameState[row][column] == player.GetColor())
            {
                stoneCount++;
            }
        }
    }

    return stoneCount;
}

Coord Board::GetSize() const
{
    return {(uint8_t)mGameState.size(), (uint8_t)mGameState.front().size()};
}

void Board::FillBoardWith(const Player &aPlayer)
{
    for (uint8_t row = 0; row < GetSize().GetXY().first; row++)
    {
        for (uint8_t column = 0; column < GetSize().GetXY().second; column++)
        {
            if (IsStoneOnPos({row, column}))
            {
                continue;
            }

            mGameState[row][column] = aPlayer.GetColor();
        }
    }
}

bool Board::CanPlayerPlaceAnyStone(const Player &player) const
{
    for (uint8_t row = 0; row < GetSize().GetXY().first; row++)
    {
        for (uint8_t column = 0; column < GetSize().GetXY().second; column++)
        {
            for (const auto &[joker, state] : player.GetJokers())
            {
                // if the joker is used check for a joker free move
                if (!state)
                {
                    if (mGameState[row][column] == player.GetColor())
                    {
                        Player playerNONE(Player::Color::NONE); // empty space
                        if (IsSameStoneNearbyPos(playerNONE, {row, column}))
                        {
                            return true;
                        }
                    }

                    continue;
                }

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
                    if (mGameState[row][column] == player.GetColor() &&
                        GetSameStoneNearbyPosCount(player, {row, column}) < MAX_NEARBY_STONES_COUNT)
                    {
                        return true;
                    }
                }
                break;

                // DOUBLE_MOVE is the same as a joker free move and
                default: {
                    if (mGameState[row][column] == player.GetColor())
                    {
                        Player playerNONE(Player::Color::NONE); // empty space
                        if (IsSameStoneNearbyPos(playerNONE, {row, column}))
                        {
                            return true;
                        }
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

    vector<uint8_t> stoneCountPlayers{};
    for (const auto &player : players)
    {
        stoneCountPlayers.push_back(GetPlayerStoneCount(player));
    }

    uint8_t winnerIndex = 0;
    uint8_t stoneCountPlayerBest = stoneCountPlayers.front();
    for (uint8_t i = 1; i < stoneCountPlayers.size(); i++)
    {
        if (stoneCountPlayers[i] >= stoneCountPlayerBest)
        {
            stoneCountPlayerBest = stoneCountPlayers[i];
            winnerIndex = i;
        }
    }

    return players[winnerIndex].GetColor();
}
}; // namespace Game
