#pragma once

namespace Game
{
/**
 * @brief Two uint8_t container
 */
class Coord
{
  public:
    // we need to add those by our own because the values can be the binary 0 and we cannot serialze those values
    friend void to_json(nlohmann::json &j, const Coord &pos);
    friend void from_json(const nlohmann::json &j, Coord &pos);

    /**
     * @brief Constructor
     * @param x the first value
     * @param y the second value
     */
    Coord(const uint8_t x, const uint8_t y);

    /**
     * @brief Gets the values
     * @return the values
     */
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

    /**
     * @brief Constructor
     * @param pos the position of the stone
     */
    Stone(const Coord &pos);

    /**
     * @brief Gets the position of the stone
     * @return the stone position
     */
    const Coord &GetPosition() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const Stone &) const = default;

  private:
    Coord mPosition;
};
}; // namespace Game
