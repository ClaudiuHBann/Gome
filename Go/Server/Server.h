#pragma once

#include "Go/Server/Match.h"
#include "Go/Server/MatchManager.h"
#include "Gome/Networking/Server/TCPServer.h"

namespace Server
{
using namespace Networking;
using namespace Networking::Server;

/**
 * @brief Accepts clients and sends them for further processing
 */
class Server : public TCPServer
{
  public:
    /**
     * @brief Constructor
     * @param context the context
     * @param port the port that we bind to
     * @param rules the rules of the match
     */
    Server(IOContext &context, const uint16_t port, Rules &rules);

  private:
    Rules &mRules;
    vector<MatchManager> mMatchManagers{};
    list<Match> mMatches{}; // list doesn't reallocate and invalidate references

    mutex mMutexPlayersWaiting{};
    vector<shared_ptr<TCPClient>> mPlayersWaiting{};

    /**
     * @brief Handler for when enough players connects to the server
     */
    void HandlePlayersWaiting();
};
} // namespace Server
