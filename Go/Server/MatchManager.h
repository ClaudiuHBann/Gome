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

/**
 * @brief The manager of a match
 */
class MatchManager
{
  public:
    /**
     * @brief Constructor
     * @param clients the tcp clients of the match
     * @param match the match
     */
    MatchManager(const vector<shared_ptr<TCPClient>> &clients, Match &match);

    /**
     * @brief Processes the match players
     */
    void Process();

  private:
    /**
     * @brief The type of errors that a player can do
     */
    enum class Error
    {
        NONE,
        TURN,  // not the turn of the requesting player
        JOKER, // joker already used
        STONE  // could not add stone
    };

    Match &mMatch;
    vector<shared_ptr<TCPClient>> mClients{};
    shared_ptr<mutex> mMutexPlayerCurrent;

    /**
     * @brief Finishes the game
     * @param client the client that will be disconnected
     */
    void Finish(shared_ptr<TCPClient> client);

    /**
     * @brief Creates a response based on the context that the player sends
     * @param contextRequest the client's context
     * @param error the error that the player did
     * @return
     */
    string CreateResponse(const ContextClient &contextRequest, const Error error);

    /**
     * @brief Handles the client processing
     * @param client the client to be processed
     */
    void ProcessPlayer(shared_ptr<TCPClient> client);

    /**
     * @brief Processes the player context
     * @param player the player
     * @param message the informative message
     * @return the context as json
     */
    string ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message);

    /**
     * @brief Gets the player associated with the client
     * @param client the client
     * @return the player
     */
    Player &GetPlayerByClient(const shared_ptr<TCPClient> &client);
};
} // namespace Server
