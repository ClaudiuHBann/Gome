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
    Match &mMatch;
    vector<shared_ptr<TCPClient>> mClients{};
    shared_ptr<mutex> mMutexPlayerCurrent;

    /**
     * @brief Send the init context and a server context
     * @param client the client to send contexts to
     * @param callback the callback to be invoked when the operation finishes
     */
    void SendContextStarting(shared_ptr<TCPClient> client, function<void()> callback);

    /**
     * @brief Finishes the game
     * @note Sends to every client the uninit context and disconnects them from the server
     */
    void Finish();

    /**
     * @brief Creates a response based on the context that the player sends
     * @param contextRequest the client's context
     * @param error the error that the player did
     * @return the context
     */
    ContextServer CreateResponse(const ContextClient &contextRequest, const ContextServer::Error error);

    /**
     * @brief Handles the client processing
     * @param client the client to be processed
     */
    void ProcessPlayer(shared_ptr<TCPClient> client);

    /**
     * @brief Send the specific context to every connected client except the passed client
     * @param contextServer the context to finish building and send
     * @param client the client to except
     */
    void SendContextServerToEveryoneExcept(ContextServer contextServer, shared_ptr<TCPClient> clientExcept);

    /**
     * @brief Processes the player context
     * @param player the player
     * @param message the informative message
     * @return the context
     */
    ContextServer ProcessPlayerMessage(Player &player, shared_ptr<MessageManager::MessageDisassembled> message);

    /**
     * @brief Gets the player associated with the client
     * @param client the client
     * @return the player
     */
    Player &GetPlayerByClient(const shared_ptr<TCPClient> &client);
};
} // namespace Server
