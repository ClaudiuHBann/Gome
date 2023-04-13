#pragma once

#include <Gome/Networking/Client/TCPClient.h>
using namespace Networking::Client;

class Client
{
  private:
    shared_ptr<TCPClient> mClient;
};
