#pragma once

#include "Go/Game/Board.h"
#include "Go/Game/Context.h"
#include "Go/Game/Player.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Client
{
using namespace Game;
using namespace Networking;
using namespace Networking::Client;

/**
 * @brief Send/Receive(s) contexts between the server
 */
class Client
{
  public:
    /**
     * @brief Constructor
     * @param context the context
     */
    Client(IOContext &context);

    /**
     * @brief Connects to the host and invokes the init callback and starts to continously receiving contexts
     * @param ip the ip of the host
     * @param port the port of the host
     * @param callbackInit the callback to be invoked when initializing
     * @param callback the callback to be invoked when receiving a context
     */
    void Start(const string &ip, const uint16_t port, function<void(ContextServerInit)> callbackInit,
               function<void(ContextServer)> callback);

    /**
     * @brief Sends the context to the connected host
     * @param context the context to be send
     */
    void Send(ContextClient &context);

    /**
     * @brief Disconnects from the host
     */
    void Disconnect();

  private:
    IOContext &mContext;
    TCPClient mClient;

    /**
     * @brief Receives the initialize context
     * @param callback the callback to be invoked when the operation completes
     */
    void Init(function<void(ContextServerInit)> callback);

    /**
     * @brief Receives contexts
     * @param callback the callback to be invoked when the operation completes
     */
    void Receive(function<void(ContextServer)> callback);

    void ReceiveCallback(function<void(ContextServer)> callback, const ContextServer &context);
};
} // namespace Client
