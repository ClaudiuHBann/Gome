#pragma once

#include "Gome/Networking/Message/MessageManager.h"
#include "Match.h"

namespace Server
{
class MatchManager
{
  public:
    MatchManager(const Match &match);

    void Process();

  private:
    void ProcessPlayer(Player &player);
    void ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message);

    shared_ptr<Match> mMatch;
};
} // namespace Server
