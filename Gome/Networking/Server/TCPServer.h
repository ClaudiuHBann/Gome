#pragma once

#include "Gome/Networking/Server/TCPServerRaw.h"

namespace Networking::Server
{
using namespace Client;

class TCPServer
{
  public:
    using CallbackAccept = function<void(shared_ptr<TCPClient>)>;

    TCPServer(const IOContext &context, const port_type port);

    void Start(CallbackAccept callback);

  private:
    shared_ptr<TCPServerRaw> mServer;
};
} // namespace Networking::Server
