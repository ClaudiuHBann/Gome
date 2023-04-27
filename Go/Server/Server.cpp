#include "Go/pch.h"

#include "Gome/Networking/Client/TCPClient.h"
#include "MatchManager.h"
#include "Server.h"

namespace Server
{
// TODO: remove all parameters except first 2
Server::Server(const IOContext &context, const port_type port, const uint8_t playersPerMatch /* = 2 */,
               const Coord &size /* = { 6, 10 } */)
    : TCPServer(context, port), mPlayersPerMatch(playersPerMatch)
{
    Start([=, this](shared_ptr<Networking::Client::TCPClient> client) {
        scoped_lock lock(mMutex);

        mPlayersWaiting.push_back(client);
        if (mPlayersPerMatch == mPlayersWaiting.size())
        {
            mMatchManagers.push_back(MatchManager(mPlayersWaiting, playersPerMatch, size));
            mMatchManagers.back().Process();

            mPlayersWaiting.clear();
        }
    });
}
} // namespace Server
