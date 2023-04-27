#pragma once

#include "Go/Game/Player.h"
#include "Go/Server/Match.h"
#include "Gome/Networking/Message/MessageManager.h"

namespace Networking::Client
{
class TCPClient;
}

namespace Server
{
using namespace Game;
using namespace Networking::Client;
using namespace Networking::Message;

class MatchManager
{
  public:
    // TODO: use dependency injection for the match
    MatchManager(const vector<shared_ptr<TCPClient>> &clients, const uint8_t playersPerMatch, const Coord &size);

    void Process();

  private:
    Match CreateMatch(vector<shared_ptr<TCPClient>> clients, const uint8_t playersPerMatch, const Coord &size);

    void ProcessPlayer(shared_ptr<TCPClient> client);
    Networking::Message::Message ProcessPlayerMessage(Player &player,
                                                      shared_ptr<MessageManager::MessageDisassembled> message);

    Player &GetPlayerByClient(const shared_ptr<TCPClient> &client);

    shared_ptr<Match> mMatch{};
    vector<shared_ptr<TCPClient>> mClients{};
};
} // namespace Server
