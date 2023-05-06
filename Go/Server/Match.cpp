#include "Go/pch.h"

#include "Go/Game/Stone.h"
#include "Gome/Utility/Random.h"
#include "Match.h"

namespace Server
{
Match::Match(const uint8_t playersPerMatch, const Coord &size) : mBoard(size)
{
    CreateMatch(playersPerMatch, size);
}

void Match::CreateMatch(const uint8_t playersPerMatch, const Coord &size)
{
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((uint32_t)seed));

    for (size_t i = 0; i < playersPerMatch; i++)
    {
        Player player((Player::Color)colors[i]);
        mPlayers.push_back(player);
    }

    Random random;
    vector<Coord> stonePoss{};
    auto &&sizeValues = size.GetXY();
    for (size_t i = 0; i < mPlayers.size(); i++)
    {
        while (true)
        {
            auto row = (uint8_t)random.Get(1ui16, (uint16_t)sizeValues.first);
            auto col = (uint8_t)random.Get(1ui16, (uint16_t)sizeValues.second);

            bool same = false;
            for (const auto &stonePos : stonePoss)
            {
                if (stonePos == Coord(row, col))
                {
                    same = true;
                    break;
                }
            }

            if (!same)
            {
                break;
            }
        }
    }

    for (size_t i = 0; i < mPlayers.size(); i++)
    {
        Stone stone(stonePoss[i]);
        mBoard.AddStone(mPlayers[i], stone);
    }

    mPlayerCurrentIndex = random.Get<decltype(mPlayerCurrentIndex)>(0, mPlayers.size() - 1);
}

size_t Match::GetPlayerCount() const
{
    return mPlayers.size();
}

Player &Match::GetPlayerCurrent()
{
    return mPlayers[mPlayerCurrentIndex];
}

Player &Match::GetPlayerNext()
{
    mPlayerCurrentIndex = (mPlayerCurrentIndex + 1) % mPlayers.size();
    return GetPlayerCurrent();
}

size_t Match::GetPlayerIndex() const
{
    return mPlayerCurrentIndex;
}
} // namespace Server
