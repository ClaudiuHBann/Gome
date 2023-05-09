#include "Gome/pch.h"

#include "MessageConverter.h"

namespace Networking::Message
{
/* static */ bytes MessageConverter::MessageToBytes(const Message &message)
{
    auto &&bytes = PacketMetadataToBytes(message.mPacketMetadata);
    auto &&bytesPacketDatas = PacketDatasToBytes(message.mPacketDatas);
    bytes.append_range(bytesPacketDatas);

    return bytes;
}

/* static */ Message MessageConverter::BytesToMessage(const bytes &bytess)
{
    bytes packetMetadataAsBytes(bytess.begin(), bytess.begin() + HeaderMetadata::SIZE);

    auto &&packetMetadata = BytesToPacketMetadata(packetMetadataAsBytes);
    Message message(packetMetadata);

    bytes packetDatasAsBytes(bytess.begin() + HeaderMetadata::SIZE, bytess.end());
    message.mPacketDatas = move(BytesToPacketDatas(packetDatasAsBytes));

    return message;
}

/* static */ bytes MessageConverter::PacketMetadataToBytes(const PacketMetadata &packetMetadata)
{
    return HeaderMetadataToBytes(packetMetadata.GetHeaderMetadata());
}

/* static */ bytes MessageConverter::PacketDataToBytes(const PacketData &packetData)
{
    auto &&bytes(HeaderDataToBytes(packetData.GetHeaderData()));
    bytes.append_range(packetData.GetContent());

    return bytes;
}

/* static */ PacketData MessageConverter::BytesToPacketData(const bytes &bytess)
{
    THROW_INVALID_ARG_IF(bytess.size() > PacketData::SIZE);

    bytes headerAsBytes(bytess.begin(), bytess.begin() + HeaderData::SIZE);
    auto &&header = BytesToHeaderData(headerAsBytes);

    bytes contentAsBytes(bytess.begin() + HeaderData::SIZE, bytess.end());

    return PacketData(header, contentAsBytes);
}

/* static */ vector<PacketData> MessageConverter::BytesToPacketDatas(const bytes &bytess)
{
    vector<PacketData> packetDatas;

    // create the last packets of data
    auto packetDatasCount = bytess.size() / PacketData::SIZE;
    for (size_t i = 0; i < packetDatasCount; i++)
    {
        bytes packetDataAsBytes(bytess.begin() + i * PacketData::SIZE, bytess.begin() + (i + 1) * PacketData::SIZE);
        packetDatas.push_back(BytesToPacketData(packetDataAsBytes));
    }

    // create the last packet data if exists
    auto packetDatasLastSize = bytess.size() % PacketData::SIZE;
    if (packetDatasLastSize)
    {
        bytes packetDataAsBytes(bytess.begin() + packetDatasCount * PacketData::SIZE,
                                bytess.begin() + packetDatasCount * PacketData::SIZE + packetDatasLastSize);
        packetDatas.push_back(BytesToPacketData(packetDataAsBytes));
    }

    return packetDatas;
}

/* static */ PacketMetadata MessageConverter::BytesToPacketMetadata(const bytes &bytes)
{
    return BytesToHeaderMetadata(bytes);
}

/* static */ bytes MessageConverter::PacketDatasToBytes(const vector<PacketData> &packetDatas)
{
    bytes bytes;

    for (const auto &packetData : packetDatas)
    {
        bytes.append_range(PacketDataToBytes(packetData));
    }

    return bytes;
}

/* static */ bytes MessageConverter::HeaderMetadataToBytes(const HeaderMetadata &headerMetadata)
{
    bytes headerAsBytes;

    auto guidRawAsBytePtr = (byte *)&headerMetadata.GetGUID().GetUUID();
    bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + Utility::GUID::GUID_SIZE);
    headerAsBytes.append_range(guidRawAsBytes);

    headerAsBytes.push_back((byte)headerMetadata.GetType());

    auto sizeAsBytePtr = (byte *)&headerMetadata.GetSize();
    bytes sizeAsBytes(sizeAsBytePtr, sizeAsBytePtr + sizeof(headerMetadata.GetSize()));
    headerAsBytes.append_range(sizeAsBytes);

    return headerAsBytes;
}

/* static */ HeaderMetadata MessageConverter::BytesToHeaderMetadata(const bytes &bytess)
{
    THROW_INVALID_ARG_IF(bytess.size() != HeaderMetadata::SIZE);

    bytes guidAsBytes(bytess.begin(), bytess.begin() + Utility::GUID::GUID_SIZE);
    Utility::GUID guid;
    guid.SetUUID(*reinterpret_cast<UUID *>(guidAsBytes.data()));
    THROW_INVALID_ARG_IF(!guid.GetStr());

    auto type = (HeaderMetadata::Type)bytess[Utility::GUID::GUID_SIZE];
    THROW_INVALID_ARG_IF(HeaderMetadata::Type::NONE > type || type > HeaderMetadata::Type::COUNT);

    bytes sizeAsBytes(bytess.begin() + Utility::GUID::GUID_SIZE + sizeof(HeaderMetadata::Type),
                      bytess.begin() + HeaderMetadata::SIZE);
    auto size = *reinterpret_cast<size_t *>(sizeAsBytes.data());

    return HeaderMetadata(guid, type, size);
}

/* static */ bytes MessageConverter::HeaderDataToBytes(const HeaderData &headerData)
{
    bytes headerAsBytes;

    auto guidRawAsBytePtr = (byte *)&headerData.GetGUID().GetUUID();
    bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + Utility::GUID::GUID_SIZE);
    headerAsBytes.append_range(guidRawAsBytes);

    auto indexValidAsBytePtr = (byte *)&headerData.GetIndex();
    bytes indexValidAsBytes(indexValidAsBytePtr, indexValidAsBytePtr + sizeof(headerData.GetIndex()));
    headerAsBytes.append_range(indexValidAsBytes);

    return headerAsBytes;
}

/* static */ HeaderData MessageConverter::BytesToHeaderData(const bytes &bytess)
{
    THROW_INVALID_ARG_IF(bytess.size() != HeaderData::SIZE);

    bytes guidAsBytes(bytess.begin(), bytess.begin() + Utility::GUID::GUID_SIZE);
    Utility::GUID guid;
    guid.SetUUID(*reinterpret_cast<UUID *>(guidAsBytes.data()));
    THROW_INVALID_ARG_IF(!guid.GetStr());

    bytes indexAsBytes(bytess.begin() + Utility::GUID::GUID_SIZE, bytess.begin() + HeaderData::SIZE);
    auto index = *reinterpret_cast<size_t *>(indexAsBytes.data());

    return HeaderData(guid, index);
}
} // namespace Networking::Message
