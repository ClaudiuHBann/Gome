#pragma once

#include "Gome/Networking/Client/TCPClient.h"
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

    Player(shared_ptr<Networking::Client::TCPClient> client, const Color color);

    void AddStone(const Stone &stone);
    void RemoveStone(const Stone &stone);

    Color GetColor();
    shared_ptr<Networking::Client::TCPClient> GetClient();

  private:
    Color mColor{};
    vector<Stone> mStones{};

    shared_ptr<Networking::Client::TCPClient> mClient;
};
