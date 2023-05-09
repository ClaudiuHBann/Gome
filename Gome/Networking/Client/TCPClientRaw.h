#pragma once

#include "Gome/Networking/IOContext.h"
#include "Gome/Utility/String.h"

namespace Networking::Client
{
using namespace Utility;

/**
 * @brief Async TCP client base class
 */
class TCPClientRaw : public enable_shared_from_this<TCPClientRaw>
{
  public:
    using CallbackConnect = function<void(error_code, shared_ptr<tcp::endpoint>)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, shared_ptr<bytes>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    /**
     * @brief Constructor
     * @param socket the socket of the client
     */
    TCPClientRaw(tcp::socket &&socket);

    /**
     * @brief Destructor
     */
    ~TCPClientRaw();

    /**
     * @brief Gets the undeyling socket
     * @return the client's socket
     */
    const unique_ptr<tcp::socket> &GetSocket() const;

    /**
     * @brief Connects to the first good endpoint
     * @param endpoints endpoints for trying to connect to
     * @param callback the callback to be invoked when connecting finishes
     */
    void ConnectAsync(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback);

    /**
     * @brief Disconnects from the host
     * @param callback the callback to be invoked when disconnecting finishes
     */
    void Disconnect(CallbackDisconnect callback = [](auto, auto) {});

    /**
     * @brief Sends a stream of bytes
     * @note Could send just a chunk of the stream of bytes
     * @param data a stream of bytes
     * @param callback the callback to be invoked when sending finishes
     */
    void SendAsync(const shared_ptr<bytes> &data, CallbackSend callback);

    /**
     * @brief Sends all the stream of bytes
     * @param data a stream of bytes
     * @param callback the callback to be invoked when sending finishes
     */
    void SendAllAsync(const shared_ptr<bytes> &data, CallbackSend callback);

    /**
     * @brief Receives a stream of bytes and populates the data
     * @note data must have the size of the buffer
     * @note Could receive just a chunk of the buffer
     * @param data the stream of bytes
     * @param callback the callback to be invoked when receiving finishes
     */
    void ReceiveAsync(const shared_ptr<bytes> &data, CallbackRead callback);

    /**
     * @brief Receives all the stream of bytes and populates the data
     * @note data must have the size of the buffer
     * @param data the stream of bytes
     * @param callback the callback to be invoked when receiving finishes
     */
    void ReceiveAllAsync(const shared_ptr<bytes> &data, CallbackRead callback);

  private:
    /**
     * @brief Sends all the stream of bytes per chunks recursively
     * @param data the stream of bytes
     * @param offset the offset to start sending again
     * @param callback the callback to be invoked when sending finishes
     */
    void SendShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackSend callback);

    /**
     * @brief Receives all the stream of bytes per chunks recursively
     * @note data must have the size of the buffer
     * @param data the stream of bytes
     * @param offset the offset to start receiving again
     * @param callback the callback to be invoked when receiving finishes
     */
    void ReceiveShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackRead callback);

    unique_ptr<tcp::socket> mSocket;
};
} // namespace Networking::Client
