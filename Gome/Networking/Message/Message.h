#pragma once

#include "Packet.h"

namespace Networking::Message
{
class MessageManager;
class MessageConverter;

class Message
{
    friend class MessageManager;
    friend class MessageConverter;

    Message(const PacketMetadata &packetMetadata);

    PacketMetadata mPacketMetadata;
    vector<PacketData> mPacketDatas;

  public:
    const PacketMetadata &GetPacketMetadata() const;
    const vector<PacketData> &GetPacketDatas() const;
};
} // namespace Networking::Message