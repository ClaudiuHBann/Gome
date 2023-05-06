#pragma once

namespace Game
{
class Coord
{
  public:
    Coord(const uint8_t x, const uint8_t y);

    pair<uint8_t, uint8_t> GetXY() const;

    auto operator<=>(const Coord &) const = default;

  private:
    uint8_t mX{};
    uint8_t mY{};
};

class Stone
{
  public:
    Stone(const Coord &pos);

    const Coord &GetPosition() const;

    auto operator<=>(const Stone &) const = default;

  private:
    Coord mPosition;
};
}; // namespace Game
