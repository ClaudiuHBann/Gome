#pragma once

namespace Game
{
class Stone;
class Coord;

class Player
{
  public:
    enum class Color : uint8_t
    {
        UNKNOWN,
        BLACK,
        RED,
        GREEN,
        BLUE,
        WHITE
    };

    Player(const Color color);

    void StoneAdd(const Stone &stone);
    void StoneMove(const Stone &stone, const Coord &pos);

    Color GetColor() const;

  private:
    Color mColor = Color::UNKNOWN;
    list<Stone> mStones{};
};
}; // namespace Game
