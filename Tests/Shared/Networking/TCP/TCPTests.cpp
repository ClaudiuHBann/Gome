#include "Tests/pch.h"
//
#include "TCPTests.h"
//

namespace Shared
{
namespace Networking
{
namespace TCP
{
using namespace Server;
using namespace Client;

constexpr auto SERVER_IP = TEXT("127.0.0.1");
constexpr auto SERVER_PORT = 6969;

constexpr auto TEST_DATA_BYTES_SIZE = 1'000'000;
constexpr auto TEST_DATA_TYPE = HeaderMetadata::Type::PING;

TCPTests::TCPTests() : mServer(mContext, SERVER_PORT), mClient(mContext.CreateSocket())
{
    TEST_DATA_BYTES.resize(TEST_DATA_BYTES_SIZE);
    for (size_t i = 0; i < TEST_DATA_BYTES_SIZE; i++)
    {
        TEST_DATA_BYTES[i] = byte(i);
    }
}

void TCPTests::Fail(const String &methodName)
{
    mSucceededServer = false;
    mSucceededClient = false;
    mContext.Stop();

    TRACE(methodName << TEXT("\t\t\tFAILED"));
}

bool TCPTests::Test()
{
    TestServer();
    TestClient();

    mContext.Run();

    return mSucceededServer && mSucceededClient;
}

void TCPTests::TestServer()
{
    mServer.Start([this](auto client) {
        client->Receive([this, client](auto, auto tuple) {
            auto &&[guid, type, bytes] = tuple;

            if (bytes == TEST_DATA_BYTES && type == TEST_DATA_TYPE)
            {
                client->Send(bytes, type, [this](auto ec, auto) {
                    if (ec)
                    {
                        Fail(TEXT("TestServer"));
                    }
                    else
                    {
                        mSucceededServer = true;

                        TRACE(TEXT("TestServer") << TEXT("\t\t\tSUCCEEDED"));
                    }
                });
            }
            else
            {
                Fail(TEXT("TestServer"));
            }
        });
    });
}

void TCPTests::TestClient()
{
    auto &&resolver = mContext.CreateResolver();
    auto &&endpoints =
        resolver.resolve(ToStringType<char>(String(SERVER_IP)), ToStringType<char>(ToString(SERVER_PORT)));

    mClient.Connect(endpoints, [this](auto ec, auto) {
        if (ec)
        {
            Fail(TEXT("TestClient"));
        }
        else
        {
            mClient.Send(TEST_DATA_BYTES, TEST_DATA_TYPE, [this](auto ec, auto) {
                if (ec)
                {
                    Fail(TEXT("TestClient"));
                }
                else
                {
                    mClient.Receive([this](auto, auto tuple) {
                        auto &&[guid, type, bytes] = tuple;

                        if (bytes == TEST_DATA_BYTES && type == TEST_DATA_TYPE)
                        {
                            mSucceededClient = true;
                            mContext.Stop();

                            TRACE(TEXT("TestClient") << TEXT("\t\t\tSUCCEEDED"));
                        }
                        else
                        {
                            Fail(TEXT("TestClient"));
                        }
                    });
                }
            });
        }
    });
}
} // namespace TCP
} // namespace Networking
} // namespace Shared
