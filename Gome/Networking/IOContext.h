#pragma once

namespace Networking
{
class IOContext
{
  public:
    IOContext();

    tcp::socket CreateSocket();
    tcp::resolver CreateResolver();
    tcp::acceptor CreateAcceptor();

    void Run();
    void Stop();

    io_context &operator*();

  private:
    unique_ptr<io_context> mIOContext{};
};
} // namespace Networking
