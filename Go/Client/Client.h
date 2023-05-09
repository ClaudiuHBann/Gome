#pragma once

#include "Go/Game/Board.h"
#include "Go/Game/Context.h"
#include "Go/Game/Player.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Client
{
using namespace Game;
using namespace Networking;
using namespace Networking::Client;

class Client
{
  public:
    Client(IOContext &context);

    void Start(const string &ip, const uint16_t port, function<void(ContextServerInit)> callbackInit,
               function<void(ContextServer)> callback);
    void Send(ContextClient &context);

  private:
    IOContext &mContext;
    TCPClient mClient;

    void Init(function<void(ContextServerInit)> callback);
    void Receive(function<void(ContextServer)> callback);
};
} // namespace Client
