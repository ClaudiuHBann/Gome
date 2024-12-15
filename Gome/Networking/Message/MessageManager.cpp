#include "Gome/pch.h"

#include "MessageManager.h"

namespace Networking::Message
{
/* static */ Message MessageManager::ToMessage(const bytes &bytess, HeaderMetadata::Type type,
                                               Utility::GUID guid /* = {} */)
{
    vector<PacketData> packetDatas;

    // create the packets of data of the message
    auto packetsCount = bytess.size() / PacketData::CONTENT_SIZE_MAX;
    for (size_t i = 0; i < packetsCount; i++)
    {
        HeaderData headerData(guid, i);
        bytes content(bytess.begin() + i * PacketData::CONTENT_SIZE_MAX,
                      bytess.begin() + (i + 1) * PacketData::CONTENT_SIZE_MAX);
        PacketData packetData(headerData, content);

        packetDatas.push_back(packetData);
    }

    // create the last message with variant size if exists
    auto packetLastSize = bytess.size() % PacketData::CONTENT_SIZE_MAX;
    if (packetLastSize)
    {
        HeaderData headerData(guid, packetsCount);
        bytes content(bytess.begin() + packetsCount * PacketData::CONTENT_SIZE_MAX, bytess.end());
        PacketData packetData(headerData, content);

        packetDatas.push_back(packetData);
    }

    // get the message's size and create it
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
        bytes.insert(bytes.begin() + packetData.GetHeaderData().GetIndex() * PacketData::CONTENT_SIZE_MAX,
                     packetData.GetContent().begin(), packetData.GetContent().end());
    }

    return {message.mPacketMetadata.GetHeaderMetadata().GetGUID(),
            message.mPacketMetadata.GetHeaderMetadata().GetType(), bytes};
}
} // namespace Networking::Message
