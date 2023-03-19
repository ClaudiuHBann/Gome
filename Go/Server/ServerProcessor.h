#pragma once

#include "Go/Match.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Server
{
using namespace Networking;
using namespace Client;

class ServerProcessor
{
  public:
    void Process(vector<shared_ptr<TCPClient>> clients);

  private:
    vector<Match> mMatches;
};
} // namespace Server
