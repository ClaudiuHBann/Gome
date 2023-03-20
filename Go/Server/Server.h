#pragma once

#include "Gome/Networking/Server/TCPServer.h"

namespace Server
{
using namespace Networking::Server;
using namespace Networking;

class Server
{
  public:
    Server(const IOContext &context);

  private:
    vector<shared_ptr<TCPClient>> mPlayersWaiting{};

    TCPServer mServer;
};

} // namespace Server
