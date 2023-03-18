#include "Gome/pch.h"
//
#include "TCPServer.h"
//

namespace Shared::Networking::Server
{
using namespace Client;

TCPServer::TCPServer(const IOContext &context, const port_type port) : mServer(make_shared<TCPServerRaw>(context, port))
{
}

void TCPServer::Start(CallbackAccept callback)
{
    mServer->Start(move(callback));
}
} // namespace Shared::Networking::Server
