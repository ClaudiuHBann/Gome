#include "Gome/pch.h"
//
#include "TCPServer.h"
//

namespace Networking::Server
{
using namespace Client;

TCPServer::TCPServer(IOContext &context, const port_type port) : mServer(make_shared<TCPServerRaw>(context, port))
{
}

void TCPServer::Start(CallbackAccept callback)
{
    mServer->Start(move(callback));
}
} // namespace Networking::Server
