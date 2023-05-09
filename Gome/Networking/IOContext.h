#pragma once

namespace Networking
{
/**
 * @brief Wrapper for asio::io_context
 */
class IOContext
{
  public:
    /**
     * @brief Constructor
     */
    IOContext();

    /**
     * @brief Creates a tcp socket
     * @return the tcp socket
     */
    tcp::socket CreateSocket();

    /**
     * @brief Creates a tcp resolver
     * @return the tcp resolver
     */
    tcp::resolver CreateResolver();

    /**
     * @brief Creates an tcp acceptor
     * @return the tcp acceptor
     */
    tcp::acceptor CreateAcceptor();

    /**
     * @brief Runs the context
     */
    void Run();

    /**
     * @brief Stops the context
     */
    void Stop();

    /**
     * @brief * operator overload for easier access of the underlying context
     * @return the asio::io_context
     */
    io_context &operator*();

  private:
    unique_ptr<io_context> mIOContext{};
};
} // namespace Networking
