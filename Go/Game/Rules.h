#pragma once

#include "Stone.h"

namespace Game
{
class Rules
{
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rules, mPlayersPerMatch, mSize)

  public:
    Rules(const uint8_t playersPerMatch, const Coord &size);

    uint8_t GetPlayersPerMatch() const;
    const Coord &GetSize() const;

  private:
    uint8_t mPlayersPerMatch{};
    Coord mSize;
};
} // namespace Game
