#pragma once

#include "Gome/Shared/Networking/Server/TCPServer.h"

namespace Shared
{
namespace Networking
{
namespace TCP
{
using namespace Server;
using namespace Client;

CLASS_TEST_START(TCPTests);
TCPTests();

private:
IOContext mContext;

TCPServer mServer;
TCPClient mClient;

atomic<bool> mSucceededServer{};
atomic<bool> mSucceededClient{};

vector<byte> TEST_DATA_BYTES{};

void TestServer();
void TestClient();

void Fail(const String &methodName);
CLASS_TEST_END;
} // namespace TCP
} // namespace Networking
} // namespace Shared
