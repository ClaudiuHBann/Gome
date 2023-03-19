#include "Go/pch.h"
//
#include "ServerProcessor.h"
//

namespace Server
{
using namespace Networking;
using namespace Client;

void ServerProcessor::Process(vector<shared_ptr<TCPClient>> clients)
{
    mMatchManager.Process(ClientsToMatch(clients));
}

Match ServerProcessor::ClientsToMatch(vector<shared_ptr<TCPClient>> clients)
{
    vector<uint8_t> colors{0, 1, 2, 3, 4};

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(colors.begin(), colors.end(), default_random_engine((unsigned int)seed));

    Match match;
    for (size_t i = 0; i < PLAYERS_PER_MATCH; i++)
    {
        Player player(clients[i], (Player::Color)colors[i]);
        match.AddPlayer(player);
    }

    return match;
}
} // namespace Server
