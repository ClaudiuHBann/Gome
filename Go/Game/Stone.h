#pragma once

namespace Game
{
class Coord
{
  public:
    friend void to_json(nlohmann::json &j, const Coord &pos)
    {
        j["mX"] = (uint16_t)pos.mX;
        j["mY"] = (uint16_t)pos.mY;
    }

    friend void from_json(const nlohmann::json &j, Coord &pos)
    {
        uint16_t x{}, y{};
        j.at("mX").get_to(x);
        j.at("mY").get_to(y);
        pos.mX = (uint8_t)x, pos.mY = (uint8_t)y;
    }

    Coord(const uint8_t x, const uint8_t y);

    pair<uint8_t, uint8_t> GetXY() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const Coord &) const = default;

  private:
    uint8_t mX{};
    uint8_t mY{};
};

class Stone
{
  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Stone, mPosition)

    Stone(const Coord &pos);

    const Coord &GetPosition() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const Stone &) const = default;

  private:
    Coord mPosition;
};
}; // namespace Game
