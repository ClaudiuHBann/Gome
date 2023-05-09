#pragma once

#include "Gome/Networking/Server/TCPServer.h"

namespace Networking::TCP
{
using namespace Server;
using namespace Client;

/**
 * @brief The tests for the networking module
 */
CLASS_TEST_START(TCPTests);

/**
 * @brief Constructor
 */
TCPTests();

private:
IOContext mContext;

TCPServer mServer;
TCPClient mClient;

atomic<bool> mSucceededServer{};
atomic<bool> mSucceededClient{};

vector<byte> TEST_DATA_BYTES{};

/**
 * @brief Tests the server module of networking
 */
void TestServer();

/**
 * @brief Tests the client module of networking
 */
void TestClient();

/**
 * @brief Finishes the tests and logs the error
 * @param methodName the name of the method that failed
 */
void Fail(const String &methodName);
CLASS_TEST_END;
} // namespace Networking::TCP
