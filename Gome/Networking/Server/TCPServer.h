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

class TCPServer
{
    friend class TCPTests;

  public:
    using CallbackAccept = function<void(shared_ptr<TCPClient>)>;

    TCPServer(IOContext &context, const uint16_t port);

  protected:
    shared_ptr<TCPServerRaw> mServer;

    void Start(CallbackAccept callback);
};
} // namespace Networking::Server
