#pragma once

#include "Client.h"
#include "Stone.h"

class Player
{
  public:
    enum class Color : uint8_t
    {
        BLACK,
        RED,
        GREEN,
        BLUE,
        WHITE,
        NONE
    };

    Player(Client &&client, const Color color);

    void AddStone(const Stone &stone);
    void RemoveStone(const Stone &stone);

    Color GetColor();

  private:
    Color mColor{};
    vector<Stone> mStones{};

    Client mClient{};
};
