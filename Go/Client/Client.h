#pragma once

namespace Client
{
class TCPClient;

class Client
{
  public:
    Client(TCPClient &&client);

  private:
    shared_ptr<TCPClient> mClient;
};
} // namespace Client
