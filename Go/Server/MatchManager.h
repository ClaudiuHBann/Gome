#pragma once

#include "Go/Game/Player.h"
#include "Gome/Networking/Message/MessageManager.h"

namespace Networking::Client
{
class TCPClient;
}

class Match;

namespace Server
{
using namespace Game;
using namespace Networking::Client;
using namespace Networking::Message;

class MatchManager
{
    class Client
    {
      public:
        Player player;
        shared_ptr<TCPClient> client;
    };

  public:
    MatchManager(const list<shared_ptr<TCPClient>> &clients, const uint8_t playersPerMatch, const Coord &size);

    void Process();

  private:
    void CreateMatch(list<shared_ptr<TCPClient>> clients, const uint8_t playersPerMatch, const Coord &size);

    void ProcessPlayer(Player &player);
    Networking::Message::Message ProcessPlayerMessage(Player &player,
                                                      shared_ptr<MessageManager::MessageDisassembled> message);

    shared_ptr<TCPClient> GetTCPClient(const Player &player);

    shared_ptr<Match> mMatch{};
    vector<Client> mClients{};
};
} // namespace Server
