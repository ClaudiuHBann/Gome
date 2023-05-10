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
    using CallbackContextServerInit = function<void(ContextServerInit)>;
    using CallbackContextServer = function<void(ContextServer)>;
    using CallbackContextServerUninit = function<void(ContextServerUninit)>;

    /**
     * @brief Constructor
     * @param context the context
     * @param callbackInit the callback to be invoked when match starts
     * @param callback the callback to be invoked when match in progress
     * @param callbackUninit the callback to be invoked when match ends
     */
    Client(IOContext &context, CallbackContextServerInit callbackInit, CallbackContextServer callback,
           CallbackContextServerUninit callbackUninit);

    /**
     * @brief Connects to the host
     * @param ip the ip of the host
     * @param port the port of the host
     */
    void Connect(const string &ip, const uint16_t port);

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

    CallbackContextServerInit mCallbackInit;
    CallbackContextServer mCallback;
    CallbackContextServerUninit mCallbackUninit;

    /**
     * @brief Receives contexts
     */
    void Receive();

    /**
     * @brief Process the json and invokes the callback
     * @param jsonString the json string
     */
    void ReceiveProcess(const string &jsonString);
};
} // namespace Client
