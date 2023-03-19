#include "Go/pch.h"
//
#include "Server.h"
//

namespace Server
{
using namespace Networking::Server;

Server::Server(const IOContext &context) : mServer(context, SERVER_PORT)
{
    mServer.Start([this](auto client) {
        mPlayersWaiting.push_back(client);
        if (PLAYERS_PER_MATCH == mPlayersWaiting.size())
        {
            mServerProcessor.Process(mPlayersWaiting);
            mPlayersWaiting.clear();
        }
    });
}
} // namespace Server
