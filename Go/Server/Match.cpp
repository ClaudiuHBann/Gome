#include "Go/pch.h"

#include "Go/Game/Stone.h"
#include "Gome/Utility/Random.h"
#include "Match.h"

namespace Server
{
Match::Match(Rules &rules) : mRules(rules), mBoard(mRules.GetSize())
{
    CreateMatch(rules);
}

void Match::CreateMatch(const Rules &rules)
{
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((uint32_t)seed));

    for (size_t i = 0; i < rules.GetPlayersPerMatch(); i++)
    {
        Player player((Player::Color)colors[i]);
        mPlayers.push_back(player);
    }

    Random random;
    vector<Coord> stonePoss{};
    auto &&sizeValues = rules.GetSize().GetXY();
    for (size_t i = 0; i < mPlayers.size(); i++)
    {
        while (true)
        {
            auto row = (uint8_t)random.Get(0ui16, (uint16_t)(sizeValues.first - 1));
            auto col = (uint8_t)random.Get(0ui16, (uint16_t)(sizeValues.second - 1));

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
                stonePoss.emplace_back(row, col);
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

Player &Match::GetPlayerCurrent()
{
    return mPlayers[mPlayerCurrentIndex];
}

Player &Match::GetPlayerNext()
{
    mPlayerCurrentIndex = (mPlayerCurrentIndex + 1) % mPlayers.size();
    return GetPlayerCurrent();
}
} // namespace Server
