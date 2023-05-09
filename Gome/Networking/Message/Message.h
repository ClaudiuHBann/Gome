#pragma once

#include "Packet.h"

namespace Networking::Message
{
class MessageManager;
class MessageConverter;

/**
 * @brief The object that TCP client/server uses to communicate
 */
class Message
{
    friend class MessageManager;
    friend class MessageConverter;

    /**
     * @brief Constructor
     * @param packetMetadata the packet metadata of the message
     */
    Message(const PacketMetadata &packetMetadata);

    PacketMetadata mPacketMetadata;
    vector<PacketData> mPacketDatas;

  public:
    /**
     * @brief Gets the packet metadata
     * @return the packet metadata
     */
    const PacketMetadata &GetPacketMetadata() const;

    /**
     * @brief Gets the packets of data
     * @return the packets of data
     */
    const vector<PacketData> &GetPacketDatas() const;
};
} // namespace Networking::Message
