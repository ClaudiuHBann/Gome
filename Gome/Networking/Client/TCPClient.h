#pragma once

#include "Gome/Networking/IOContext.h"
#include "Gome/Networking/Message/MessageManager.h"
#include "TCPClientRaw.h"

namespace Networking::Client
{
using namespace Message;

/**
 * @brief Async TCP client which uses the TCPClientRaw
 */
class TCPClient
{
  public:
    using CallbackConnect = function<void(error_code, shared_ptr<tcp::endpoint>)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, shared_ptr<MessageManager::MessageDisassembled>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    /**
     * @brief Constructor
     * @param socket the underlying socket
     */
    TCPClient(tcp::socket &&socket);

    /**
     * @brief Connects to the first good endpoint
     * @param endpoints endpoints for trying to connect to
     * @param callback the callback to be invoked when connecting finishes
     */
    void Connect(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback);

    /**
     * @brief Disconnects from the host
     * @param callback the callback to be invoked when disconnecting finishes
     */
    void Disconnect(CallbackDisconnect callback = [](auto, auto) {});

    /**
     * @brief Sends all the stream of bytes
     * @param data the stream of bytes
     * @param type the type of the stream of bytes
     * @param callback the callback to be invoked when sending finishes
     */
    void Send(const bytes &data, const HeaderMetadata::Type type, CallbackSend callback);

    /**
     * @brief Receives the message
     * @param callback the callback to be invoked when receiving finishes
     */
    void Receive(CallbackRead callback);

  private:
    shared_ptr<TCPClientRaw> mTCPClientRaw;
};
} // namespace Networking::Client
