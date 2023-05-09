#pragma once

#include "Go/Game/Context.h"
#include "Go/Game/Player.h"
#include "Go/Server/Match.h"
#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/Message/MessageManager.h"

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
    enum class Error
    {
        NONE,
        TURN,  // not the turn of the requesting player
        JOKER, // joker already used
        STONE  // could not add stone
    };

    string CreateResponse(const ContextClient &contextRequest, const Error error);

    void ProcessPlayer(shared_ptr<TCPClient> client);
    string ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message);

    Player &GetPlayerByClient(const shared_ptr<TCPClient> &client);

    Match &mMatch;
    vector<shared_ptr<TCPClient>> mClients{};
    shared_ptr<mutex> mMutexPlayerCurrent;
};
} // namespace Server
