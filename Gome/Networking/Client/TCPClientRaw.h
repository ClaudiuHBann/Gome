#pragma once

#include "Gome/Networking/IOContext.h"
#include "Gome/Utility/String.h"

namespace Networking::Client
{
using namespace Utility;

class TCPClientRaw : public enable_shared_from_this<TCPClientRaw>
{
  public:
    using bytes = vector<byte>;

    using CallbackConnect = function<void(error_code, shared_ptr<tcp::endpoint>)>;
    using CallbackSend = function<void(error_code, size_t)>;
    using CallbackRead = function<void(error_code, shared_ptr<bytes>)>;
    using CallbackDisconnect = function<void(error_code, error_code)>;

    TCPClientRaw(tcp::socket &&socket);
    ~TCPClientRaw();

    const unique_ptr<tcp::socket> &GetSocket() const;

    void ConnectAsync(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback);
    void Disconnect(CallbackDisconnect callback = [](auto, auto) {});

    void SendAsync(const shared_ptr<bytes> &data, CallbackSend callback);
    void SendAllAsync(const shared_ptr<bytes> &data, CallbackSend callback);
    void ReceiveAsync(const shared_ptr<bytes> &data, CallbackRead callback);
    void ReceiveAllAsync(const shared_ptr<bytes> &data, CallbackRead callback);

  private:
    void SendShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackSend callback);
    void ReceiveShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackRead callback);

    unique_ptr<tcp::socket> mSocket;
};
} // namespace Networking::Client
