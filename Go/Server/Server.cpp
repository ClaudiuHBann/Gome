#include "Go/pch.h"

#include "Gome/Networking/Client/TCPClient.h"
#include "Match.h"
#include "MatchManager.h"
#include "Server.h"

namespace Server
{
using namespace Game;

Server::Server(const IOContext &context, const port_type port, Match &match) : TCPServer(context, port)
{
    Start([&](auto client) {
        scoped_lock lock(mMutex);

        mPlayersWaiting.push_back(client);
        if (match.GetPlayerCount() == mPlayersWaiting.size())
        {
            mMatchManagers.push_back(MatchManager(mPlayersWaiting, match));
            mMatchManagers.back().Process();

            mPlayersWaiting.clear();
        }
    });
}
} // namespace Server
