#include "Go/pch.h"

#include "Server.h"

namespace Server
{
using namespace Game;

Server::Server(IOContext &context, const port_type port, Match::Rules &rules) : TCPServer(context, port), mRules(rules)
{
    TCPServer::Start([&](auto client) {
        scoped_lock lock(mMutexPlayersWaiting);

        mPlayersWaiting.push_back(client);
        if (rules.GetPlayersPerMatch() == mPlayersWaiting.size())
        {
            HandlePlayersWaiting();
        }
    });
}

void Server::HandlePlayersWaiting()
{
    Match match(mRules);
    MatchManager matchManager(mPlayersWaiting, match);

    mMatches.emplace_back(match);
    mMatchManagers.emplace_back(matchManager).Process();

    mPlayersWaiting.clear();
}
} // namespace Server
