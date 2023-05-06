#pragma once

#include "Go/Game/Player.h"

namespace Networking::Client
{
class TCPClient;
}

namespace Client
{
using namespace Game;
using namespace Networking::Client;

class Client
{
  public:
    Client(shared_ptr<TCPClient> client);

    void GetPlayerColor(function<void(Player::Color)> callback);

    void Send(const Stone &stone, const Player::Joker joker);
    void Receive(function<void(Board, string)> callback);

  private:
    shared_ptr<TCPClient> mClient;
};
} // namespace Client
