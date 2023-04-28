#pragma once

#include "Go/Game/Stone.h"
#include "Gome/Networking/Server/TCPServer.h"

namespace Server
{
using namespace Networking;
using namespace Networking::Server;

class Server : public TCPServer
{
  public:
    Server(const IOContext &context, const port_type port, Match &match);

  private:
    mutex mMutex{};
    vector<shared_ptr<Networking::Client::TCPClient>> mPlayersWaiting{};
    vector<MatchManager> mMatchManagers{};
};

} // namespace Server
