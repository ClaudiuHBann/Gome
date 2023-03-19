#pragma once

#include "Gome/Networking/Client/TCPClient.h"
#include "Gome/Networking/IOContext.h"

namespace Networking::Server
{
using namespace Client;

class TCPServerRaw : public enable_shared_from_this<TCPServerRaw>
{
  public:
    using CallbackAccept = function<void(shared_ptr<TCPClient>)>;

    TCPServerRaw(const IOContext &context, const port_type port);
    ~TCPServerRaw();

    void Start(CallbackAccept callback);

  private:
    void Accept(CallbackAccept callback);

    IOContext mContext;
    unique_ptr<tcp::acceptor> mAcceptor;
};
} // namespace Networking::Server
