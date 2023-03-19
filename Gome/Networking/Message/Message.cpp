#include "Gome/pch.h"
//
#include "Message.h"
//

namespace Networking::Message
{
Message::Message(const PacketMetadata &packetMetadata) : mPacketMetadata(packetMetadata)
{
}

const PacketMetadata &Message::GetPacketMetadata() const
{
    return mPacketMetadata;
}

const vector<PacketData> &Message::GetPacketDatas() const
{
    return mPacketDatas;
}
} // namespace Networking::Message
