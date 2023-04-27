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
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        BLUE = 34,
        WHITE = 37
    };

    Player(const Color color);

    Color GetColor() const;

  private:
    Color mColor = Color::UNKNOWN;
    vector<Stone> mStones{};
};
}; // namespace Game
