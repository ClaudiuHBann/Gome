#include "Gome/pch.h"
//
#include "MessageManager.h"
//

namespace Networking::Message
{
/* static */ Message MessageManager::ToMessage(const bytes &bytes, HeaderMetadata::Type type,
                                               Utility::GUID guid /* = {} */)
{
    vector<PacketData> packetDatas;

    auto packetsCount = bytes.size() / PacketData::CONTENT_SIZE_MAX;
    for (size_t i = 0; i < packetsCount; i++)
    {
        HeaderData headerData(guid, i);
        MessageManager::bytes content(bytes.begin() + i * PacketData::CONTENT_SIZE_MAX,
                                      bytes.begin() + (i + 1) * PacketData::CONTENT_SIZE_MAX);
        PacketData packetData(headerData, content);

        packetDatas.push_back(packetData);
    }

    auto packetLastSize = bytes.size() % PacketData::CONTENT_SIZE_MAX;
    if (packetLastSize)
    {
        HeaderData headerData(guid, packetsCount);
        MessageManager::bytes content(bytes.begin() + packetsCount * PacketData::CONTENT_SIZE_MAX, bytes.end());
        PacketData packetData(headerData, content);

        packetDatas.push_back(packetData);
    }

    auto packetDatasSize = accumulate(packetDatas.begin(), packetDatas.end(), (size_t)0,
                                      [](auto sum, const auto &packetData) { return sum + packetData.GetSize(); });

    HeaderMetadata headerMetadata(guid, type, packetDatasSize);
    PacketMetadata packetMetadata(headerMetadata);

    Message message(packetMetadata);
    message.mPacketDatas = move(packetDatas);

    return message;
}

/* static */ MessageManager::MessageDisassembled MessageManager::FromMessage(const Message &message)
{
    bytes bytes;

    for (const auto &packetData : message.mPacketDatas)
    {
        bytes.insert_range(bytes.begin() + packetData.GetHeaderData().GetIndex() * PacketData::CONTENT_SIZE_MAX,
                           packetData.GetContent());
    }

    return {message.mPacketMetadata.GetHeaderMetadata().GetGUID(),
            message.mPacketMetadata.GetHeaderMetadata().GetType(), bytes};
}
} // namespace Networking::Message
