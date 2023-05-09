#pragma once

namespace Game
{
class Coord
{
  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Coord, mX, mY)

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
