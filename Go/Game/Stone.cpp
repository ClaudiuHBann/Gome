#include "Go/pch.h"

#include "Player.h"
#include "Stone.h"

namespace Game
{
/* friend */ void to_json(nlohmann::json &j, const Coord &pos)
{
    j["mX"] = (uint16_t)pos.mX;
    j["mY"] = (uint16_t)pos.mY;
}

/* friend */ void from_json(const nlohmann::json &j, Coord &pos)
{
    uint16_t x{}, y{};
    j.at("mX").get_to(x);
    j.at("mY").get_to(y);
    pos.mX = (uint8_t)x, pos.mY = (uint8_t)y;
}

Coord::Coord(const uint8_t x, const uint8_t y) : mX(x), mY(y)
{
}

pair<uint8_t, uint8_t> Coord::GetXY() const
{
    return {mX, mY};
}

Stone::Stone(const Coord &pos) : mPosition(pos)
{
}

const Coord &Stone::GetPosition() const
{
    return mPosition;
}
}; // namespace Game
