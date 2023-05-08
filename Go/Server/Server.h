#pragma once

#include "Go/Server/Match.h"
#include "Go/Server/MatchManager.h"
#include "Gome/Networking/Server/TCPServer.h"

namespace Server
{
using namespace Networking;
using namespace Networking::Server;

class Server : public TCPServer
{
  public:
    Server(IOContext &context, const port_type port, Match::Rules &rules);

  private:
    Match::Rules &mRules;
    vector<MatchManager> mMatchManagers{};
    vector<Match> mMatches{};

    mutex mMutexPlayersWaiting{};
    vector<shared_ptr<TCPClient>> mPlayersWaiting{};

    void HandlePlayersWaiting();
};
} // namespace Server
