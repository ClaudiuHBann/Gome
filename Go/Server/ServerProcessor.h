#pragma once

#include "Gome/Networking/Client/TCPClient.h"
#include "MatchManager.h"

namespace Server
{
using namespace Networking;
using namespace Client;

class ServerProcessor
{
  public:
    void Process(vector<shared_ptr<TCPClient>> clients);

  private:
    Match ClientsToMatch(vector<shared_ptr<TCPClient>> clients);

    MatchManager mMatchManager;
};
} // namespace Server
