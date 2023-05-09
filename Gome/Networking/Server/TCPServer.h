#pragma once

#include "Gome/Networking/Server/TCPServerRaw.h"

namespace Networking::TCP
{
class TCPTests;
}

namespace Networking::Server
{
using namespace Networking::TCP;
using namespace Client;

/**
 * @brief Async TCP server which uses the TCPServerRaw
 */
class TCPServer
{
    friend class TCPTests;

  public:
    using CallbackAccept = function<void(shared_ptr<TCPClient>)>;

    /**
     * @brief Constructor
     * @param context the context
     * @param port the port of the socket for binding
     */
    TCPServer(IOContext &context, const uint16_t port);

  protected:
    shared_ptr<TCPServerRaw> mServer;

    /**
     * @brief Wrapper for the TCPServerRaw::Start()
     * @param callback the callback for an accepted client
     */
    void Start(CallbackAccept callback);
};
} // namespace Networking::Server
