#pragma once

namespace Shared::Networking {
  class IOContext {
  public:
    IOContext();

    tcp::socket CreateSocket();
    tcp::resolver CreateResolver();
    tcp::acceptor CreateAcceptor();

  private:
    unique_ptr<io_context> mIOContext{};
  };
}
