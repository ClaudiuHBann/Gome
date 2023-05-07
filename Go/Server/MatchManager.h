#pragma once

#include "Gome/Networking/Message/MessageManager.h"

namespace Networking::Client
{
class TCPClient;
}

namespace Game
{
class Player;
}

class Match;

namespace Server
{
using namespace Game;
using namespace Networking::Client;

class MatchManager
{
  public:
    MatchManager(const vector<shared_ptr<TCPClient>> &clients, Match &match);

    void Process();

  private:
    void ProcessPlayer(shared_ptr<TCPClient> client);
    Networking::Message::Message ProcessPlayerMessage(Player &player,
                                                      shared_ptr<MessageManager::MessageDisassembled> message);

    Player &GetPlayerByClient(const shared_ptr<TCPClient> &client);

    Match &mMatch;
    vector<shared_ptr<TCPClient>> mClients{};
    mutex mMutex;
};
} // namespace Server
