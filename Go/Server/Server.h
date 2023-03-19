#pragma once

#include "Gome/Networking/Server/TCPServer.h"
#include "ServerProcessor.h"

namespace Server
{
using namespace Networking::Server;

class Server
{
  public:
    Server(const IOContext &context);

  private:
    vector<shared_ptr<TCPClient>> mPlayersWaiting{};

    ServerProcessor mServerProcessor;

    TCPServer mServer;
};

} // namespace Server
