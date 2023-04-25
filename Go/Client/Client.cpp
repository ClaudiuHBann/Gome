#include "Go/pch.h"

#include "Client.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Client
{
using namespace Networking::Client;

Client::Client(shared_ptr<TCPClient> client) : mClient(client)
{
}
} // namespace Client
