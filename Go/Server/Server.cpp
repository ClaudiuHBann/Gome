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
        else
        {
            // send the every connected client how many clients needs to connect to start the match
            for (const auto &playerWaiting : mPlayersWaiting)
            {
                ContextServer context(Coord{0, 0}, ContextServer::Error::WAIT,
                                      format("Waiting for {} more player(s) to connect...",
                                             rules.GetPlayersPerMatch() - mPlayersWaiting.size()));
                auto &&contextJSONString = context.ToJSONString();

                bytes data((byte *)contextJSONString.data(),
                           (byte *)contextJSONString.data() + contextJSONString.size());
                playerWaiting->Send(data, HeaderMetadata::Type::TEXT, [](auto, auto) {});
            }
        }
    });
}

void Server::HandlePlayersWaiting()
{
    TRACE("Creating match and it's manager...");

    Match match(mRules);
    mMatches.emplace_back(match);

    MatchManager matchManager(mPlayersWaiting, mMatches.back());
    mMatchManagers.emplace_back(matchManager).Process();

    mPlayersWaiting.clear();
}
} // namespace Server
