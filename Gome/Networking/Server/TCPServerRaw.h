#pragma once

#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/IOContext.h"

namespace Networking::Server
{
using namespace Client;

/**
 * @brief Base class for tcp servers
 */
class TCPServerRaw : public enable_shared_from_this<TCPServerRaw>
{
  public:
    using CallbackAccept = function<void(shared_ptr<TCPClient>)>;

    /**
     * @brief Constructor
     * @param context the context
     * @param port port for the socket to be binded to
     */
    TCPServerRaw(IOContext &context, const uint16_t port);

    /**
     * @brief Starts listening and continously accepting for incoming connections
     * @param callback the callback to be invoked when a client connects
     */
    void Start(CallbackAccept callback);

  private:
    /**
     * @brief Internal handler for accepting a client
     * @param callback the callback to be invoked when a client connects
     */
    void Accept(CallbackAccept callback);

    IOContext &mContext;
    unique_ptr<tcp::acceptor> mAcceptor;
};
} // namespace Networking::Server
