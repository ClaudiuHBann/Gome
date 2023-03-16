#pragma once

#include "Gome/Shared/Networking/IOContext.h"
#include "Gome/Shared/Networking/Client/TCPClient.h"

namespace Shared::Networking::Client {
  class TCPServerRaw : public enable_shared_from_this<TCPServerRaw>
  {
  public:
    using CallbackAccept = function<void(TCPClient)>;

    TCPServerRaw(tcp::acceptor&& acceptor)
      : mAcceptor(make_unique<tcp::acceptor>(move(acceptor))) {
    }

    virtual ~TCPServerRaw() {
      mAcceptor->cancel();
      mAcceptor->close();
    }

    void Start(const CallbackAccept& callback) {
      Accept(callback);
    }

  private:
    void Accept(const CallbackAccept& callback)
    {
      auto self(shared_from_this());
      auto socket = make_shared<tcp::socket>();

      mAcceptor->async_accept(*socket,
        [self, socket, callback](auto ec)
      {
        if (ec) {
          self->Accept(callback);
        }
        else {
          callback(move(*socket));
        }
      });
    }

    unique_ptr<tcp::acceptor> mAcceptor;
  };
}
