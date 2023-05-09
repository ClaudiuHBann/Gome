#include "Gome/pch.h"

#include "Packet.h"

namespace Networking::Message
{
PacketMetadata::PacketMetadata(const HeaderMetadata &headerMetadata) : mHeaderMetadata(headerMetadata)
{
}

const HeaderMetadata &PacketMetadata::GetHeaderMetadata() const
{
    return mHeaderMetadata;
}

PacketData::PacketData(const HeaderData &headerData, const bytes &content) : mHeaderData(headerData)
{
    THROW_INVALID_ARG_IF(content.size() > CONTENT_SIZE_MAX);

    mContent = content;
}

const HeaderData &PacketData::GetHeaderData() const
{
    return mHeaderData;
}

const bytes &PacketData::GetContent() const
{
    return mContent;
}

const size_t PacketData::GetSize() const
{
    return mHeaderData.SIZE + mContent.size();
}
} // namespace Networking::Message
