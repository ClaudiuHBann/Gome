#include "Go/pch.h"

#include "Client.h"
#include "Gome/Networking/Client/TCPClient.h"

namespace Client
{
using namespace Networking::Client;

Client::Client(TCPClient &&client) : mClient()
{
}
} // namespace Client
