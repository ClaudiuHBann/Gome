#include "Go/pch.h"

#include "Server.h"

namespace Server
{
using namespace Game;

Server::Server(IOContext &context, const uint16_t port, Rules &rules) : TCPServer(context, port), mRules(rules)
{
    Start([&](auto client) {
        scoped_lock lock(mMutexPlayersWaiting);

        mPlayersWaiting.push_back(client);
        TRACE(format("Player no {} has connected...", mPlayersWaiting.size()).c_str());
        if (rules.GetPlayersPerMatch() == mPlayersWaiting.size())
        {
            HandlePlayersWaiting();
        }
    });
}

void Server::HandlePlayersWaiting()
{
    TRACE("Creating match and it's manager...");
    Match match(mRules);
    MatchManager matchManager(mPlayersWaiting, match);

    mMatches.emplace_back(match);
    mMatchManagers.emplace_back(matchManager).Process();

    mPlayersWaiting.clear();
}
} // namespace Server
