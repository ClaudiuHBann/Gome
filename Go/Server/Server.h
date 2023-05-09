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
    Server(IOContext &context, const uint16_t port, Rules &rules);

  private:
    Rules &mRules;
    vector<MatchManager> mMatchManagers{};
    list<Match> mMatches{}; // list doesn't reallocate and invalidate references

    mutex mMutexPlayersWaiting{};
    vector<shared_ptr<TCPClient>> mPlayersWaiting{};

    void HandlePlayersWaiting();
};
} // namespace Server
