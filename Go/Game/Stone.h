#pragma once

namespace Game
{
class Player;

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
    Stone(Player &player, const Coord &pos);

    const Coord &GetPosition() const;
    void SetPosition(const Coord &pos);

    auto operator<=>(const Stone &) const = default;

  private:
    Player &mPlayer;
    Coord mPosition;
};
}; // namespace Game
