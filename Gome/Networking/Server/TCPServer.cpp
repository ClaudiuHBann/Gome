#include "Gome/pch.h"

#include "TCPServer.h"

namespace Networking::Server
{
using namespace Client;

TCPServer::TCPServer(IOContext &context, const uint16_t port) : mServer(make_shared<TCPServerRaw>(context, port))
{
}

void TCPServer::Start(CallbackAccept callback)
{
    mServer->Start(move(callback));
}
} // namespace Networking::Server
