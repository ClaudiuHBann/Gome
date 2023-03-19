#include "Gome/pch.h"
//
#include "Packet.h"
//

namespace Networking::Message
{
PacketMetadata::PacketMetadata(const HeaderMetadata &headerMetadata) : mHeaderMetadata(headerMetadata)
{
}

const HeaderMetadata &PacketMetadata::GetHeaderMetadata() const
{
    return mHeaderMetadata;
}

bool PacketMetadata::operator==(const PacketMetadata &right)
{
    return mHeaderMetadata == right.mHeaderMetadata;
}

PacketData::PacketData(const HeaderData &headerData, const bytes &content) : mHeaderData(headerData)
{
    assert(content.size() <= CONTENT_SIZE_MAX);
    mContent = content;
}

bool PacketData::operator==(const PacketData &right)
{
    return mHeaderData == right.mHeaderData && mContent == right.mContent;
}

const HeaderData &PacketData::GetHeaderData() const
{
    return mHeaderData;
}

const PacketData::bytes &PacketData::GetContent() const
{
    return mContent;
}

const size_t PacketData::GetSize() const
{
    return mHeaderData.SIZE + mContent.size();
}
} // namespace Networking::Message
