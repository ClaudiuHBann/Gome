#pragma once

#include "TCPClientRaw.h"
#include "Gome/Shared/Networking/Message/Header.h"

namespace Shared::Networking::Client {
  using namespace Message;

  class TCPClient {
  public:
    using bytes = vector<byte>;

    using CallbackConnect = function<void(error_code, tcp::endpoint)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, tuple<Utility::GUID, HeaderMetadata::Type, bytes>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    TCPClient(tcp::socket&& socket);

    void Connect(const basic_resolver_results<tcp>& endpoints, const CallbackConnect& callback);
    void Disconnect(const CallbackDisconnect& callback = [] (auto, auto) {});

    void Send(const bytes& data, const HeaderMetadata::Type type, const CallbackSend& callback);
    void Receive(const CallbackRead& callback);

  private:
    TCPClient(const TCPClient& tcpClient) = delete;
    TCPClient& operator=(const TCPClient& tcpClient) = delete;

    shared_ptr<TCPClientRaw> mTCPClientRaw;
  };
}
