#include "Gome/pch.h"
#include "TCPClient.h"
#include "Gome/Shared/Networking/Message/MessageManager.h"
#include "Gome/Shared/Networking/Message/MessageConverter.h"

namespace Shared::Networking::Client {
  using namespace Message;

  TCPClient::TCPClient(tcp::socket&& socket)
    : mTCPClientRaw(make_shared<TCPClientRaw>(move(socket))) {
  }

  void TCPClient::Connect(const basic_resolver_results<tcp>& endpoints, const CallbackConnect& callback) {
    mTCPClientRaw->ConnectAsync(endpoints, callback);
  }

  void TCPClient::Disconnect(const CallbackDisconnect& callback /* = [] (auto, auto) {} */) {
    mTCPClientRaw->Disconnect(callback);
  }

  void TCPClient::Send(const bytes& data, const HeaderMetadata::Type type, const CallbackSend& callback) {
    auto&& message = MessageManager::ToMessage(data, type);
    auto&& bytes = MessageConverter::MessageToBytes(message);
    auto bytesShared = make_shared<TCPClient::bytes>(move(bytes));

    mTCPClientRaw->SendAllAsync(bytesShared,
      [callback](auto ec, auto size) {
      callback(ec, size);
    });
  }

  void TCPClient::Receive(const CallbackRead& callback) {
    auto metadata = make_shared<bytes>(HeaderMetadata::SIZE);
    mTCPClientRaw->ReceiveAllAsync(metadata,
      [this, callback](auto ec, auto bytes) {
      if (ec)
      {
        callback(ec, {});
      }
      else {
        auto data = make_shared<TCPClient::bytes>(bytes->size());
        mTCPClientRaw->ReceiveAllAsync(data,
          [callback](auto ec, auto bytes) {
          if (ec)
          {
            callback(ec, {});
          }
          else {
            auto&& messageBytes = MessageConverter::BytesToMessage(*bytes);
            auto&& tuple = MessageManager::FromMessage(messageBytes);

            callback(ec, move(tuple));
          }
        });
      }
    });
  }
}
