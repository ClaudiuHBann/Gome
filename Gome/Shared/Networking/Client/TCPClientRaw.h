#pragma once

#include "Gome/Shared/Utility/String.h"
#include "Gome/Shared/Networking/IOContext.h"

namespace Shared::Networking::Client {
  using namespace Utility;

  class TCPClientRaw : public enable_shared_from_this<TCPClientRaw> {
  public:
    using bytes = vector<byte>;

    using CallbackConnect = function<void(error_code, tcp::endpoint)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, shared_ptr<bytes>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    TCPClientRaw(tcp::socket&& socket);
    ~TCPClientRaw();

    const unique_ptr<tcp::socket>& GetSocket() const;

    void ConnectAsync(const basic_resolver_results<tcp>& endpoints, const CallbackConnect& callback);
    void Disconnect(const CallbackDisconnect& callback = [](auto, auto) {});

    void SendAsync(const shared_ptr<bytes>& data, const CallbackSend& callback);
    void SendAllAsync(const shared_ptr<bytes>& data, const CallbackSend& callback);
    void ReceiveAsync(const shared_ptr<bytes>& data, const CallbackRead& callback);
    void ReceiveAllAsync(const shared_ptr<bytes>& data, const CallbackRead& callback);

  private:
    TCPClientRaw(const TCPClientRaw& tcpClientRaw) = delete;
    TCPClientRaw& operator=(const TCPClientRaw& tcpClientRaw) = delete;

    void SendShardAsync(const shared_ptr<bytes>& data, const size_t offset, const CallbackSend& callback);
    void ReceiveShardAsync(const shared_ptr<bytes>& data, const size_t offset, const CallbackRead& callback);

    unique_ptr<tcp::socket> mSocket;
  };
}
