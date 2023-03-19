#pragma once

#include "Gome/Networking/IOContext.h"
#include "Gome/Networking/Message/MessageManager.h"
#include "TCPClientRaw.h"

namespace Networking::Client
{
using namespace Message;

class TCPClient
{
  public:
    using bytes = vector<byte>;

    using CallbackConnect = function<void(error_code, shared_ptr<tcp::endpoint>)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, shared_ptr<MessageManager::MessageDisassembled>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    TCPClient(tcp::socket &&socket);

    void Connect(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback);
    void Disconnect(CallbackDisconnect callback = [](auto, auto) {});

    void Send(const bytes &data, const HeaderMetadata::Type type, CallbackSend callback);
    void Receive(CallbackRead callback);

  private:
    shared_ptr<TCPClientRaw> mTCPClientRaw;
};
} // namespace Networking::Client
