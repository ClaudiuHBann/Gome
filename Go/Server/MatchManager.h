#pragma once

#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/Message/MessageManager.h"
#include "Match.h"

namespace Server
{
using namespace Networking;
using namespace Message;
using namespace Client;

class MatchManager
{
  public:
    MatchManager(vector<shared_ptr<TCPClient>> clients);

    void Process();

  private:
    void CreateMatch(vector<shared_ptr<TCPClient>> clients);

    void ProcessPlayer(Player &player);
    void ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message);

    bool IsMoveValid(Player &player, const Stone &stone);

    shared_ptr<Match> mMatch;
};
} // namespace Server
