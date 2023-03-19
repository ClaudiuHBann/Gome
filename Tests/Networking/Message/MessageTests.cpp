#include "Tests/pch.h"
//
#include "MessageTests.h"
//
#include "Gome/Networking/Message/MessageConverter.h"
#include "Gome/Networking/Message/MessageManager.h"

namespace Networking::Message
{
bool MessageTests::Test()
{
    bool succeeded = true;

    TEST_CLASS_METHOD_AND_SET_SUCCEEDED(TestMessageManager, succeeded);
    TEST_CLASS_METHOD_AND_SET_SUCCEEDED(TestMessageConverter, succeeded);

    return succeeded;
}

bool MessageTests::TestMessageConverter() const
{
    Utility::GUID guid;

    HeaderMetadata headerMetadataStart(guid, HeaderMetadata::Type::PING, 69);
    auto headerMetadataAsBytes(MessageConverter::HeaderMetadataToBytes(headerMetadataStart));
    auto headerMetadataEnd(MessageConverter::BytesToHeaderMetadata(headerMetadataAsBytes));
    CHECK_TRUE_RETURN_FALSE(headerMetadataStart == headerMetadataEnd);

    HeaderData headerDataStart(guid, 69);
    auto headerDataAsBytes(MessageConverter::HeaderDataToBytes(headerDataStart));
    auto headerDataEnd(MessageConverter::BytesToHeaderData(headerDataAsBytes));
    CHECK_TRUE_RETURN_FALSE(headerDataStart == headerDataEnd);

    PacketMetadata packetMetadataStart(headerMetadataStart);
    auto packetMetadataAsBytes(MessageConverter::PacketMetadataToBytes(packetMetadataStart));
    auto packetMetadataEnd(MessageConverter::BytesToPacketMetadata(packetMetadataAsBytes));
    CHECK_TRUE_RETURN_FALSE(packetMetadataStart == packetMetadataEnd);

    PacketData packetDataStart(headerDataStart, {(byte)'6', (byte)'9'});
    auto packetDataAsBytes(MessageConverter::PacketDataToBytes(packetDataStart));
    auto packetDataEnd(MessageConverter::BytesToPacketData(packetDataAsBytes));
    CHECK_TRUE_RETURN_FALSE(packetDataStart == packetDataEnd);

    vector<byte> bytes(12345);
    for (size_t i = 0; i < bytes.size(); i++)
    {
        bytes[i] = (byte)i;
    }
    HeaderMetadata headerMetadata(guid, HeaderMetadata::Type::PING, bytes.size());

    auto packetDatasEnd(MessageConverter::BytesToPacketDatas(bytes));
    auto packetDatasAsBytes(MessageConverter::PacketDatasToBytes(packetDatasEnd));
    CHECK_TRUE_RETURN_FALSE(bytes == packetDatasAsBytes);

    return true;
}

bool MessageTests::TestMessageManager() const
{
    Utility::GUID gu1d;

    vector<byte> dataStart(12345);
    for (size_t i = 0; i < dataStart.size(); i++)
    {
        dataStart[i] = (byte)i;
    }

    auto &&message = MessageManager::ToMessage(dataStart, HeaderMetadata::Type::TEXT, gu1d);
    auto &&[guid, type, dataEnd] = MessageManager::FromMessage(message);
    CHECK_TRUE_RETURN_FALSE(message.GetPacketMetadata().GetHeaderMetadata().GetGUID() == guid &&
                            message.GetPacketMetadata().GetHeaderMetadata().GetType() == type && dataStart == dataEnd);

    return true;
}
} // namespace Networking::Message
