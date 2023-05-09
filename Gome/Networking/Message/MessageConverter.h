#pragma once

#include "Message.h"

namespace Networking::Message
{
/**
 * @brief Converter of and message component to message and vice versa
 */
class MessageConverter
{
  public:
    /**
     * @brief Converts a message to a stream of bytes
     * @param message the message
     * @return the stream of bytes
     */
    static bytes MessageToBytes(const Message &message);

    /**
     * @brief Converts a stream of bytes to a message
     * @param bytes the stream of bytes
     * @return the message
     */
    static Message BytesToMessage(const bytes &bytes);

    /**
     * @brief Converts a packet metadata to bytes
     * @param packetMetadata the packet metadata
     * @return the stream of bytes
     */
    static bytes PacketMetadataToBytes(const PacketMetadata &packetMetadata);

    /**
     * @brief Converts a stream of bytes to a packet metadata
     * @param bytes the stream of bytes
     * @return the packet metadata
     */
    static PacketMetadata BytesToPacketMetadata(const bytes &bytes);

    /**
     * @brief Converts packets of data to a stream of bytes
     * @param packetDatas the packets of data
     * @return the stream of bytes
     */
    static bytes PacketDatasToBytes(const vector<PacketData> &packetDatas);

    /**
     * @brief Converts a stream of bytes to packets of data
     * @param bytes a stream of bytes
     * @return the packets of data
     */
    static vector<PacketData> BytesToPacketDatas(const bytes &bytes);

    /**
     * @brief Converts a header metadata to a stream of bytes
     * @param headerMetadata the header metadata
     * @return the stream of bytes
     */
    static bytes HeaderMetadataToBytes(const HeaderMetadata &headerMetadata);

    /**
     * @brief Converts a stream of bytes to a header metadata
     * @param bytes a stream of bytes
     * @return the header metadata
     */
    static HeaderMetadata BytesToHeaderMetadata(const bytes &bytes);

    /**
     * @brief Converts a header data to a stream of bytes
     * @param headerData the header data
     * @return the stream of bytes
     */
    static bytes HeaderDataToBytes(const HeaderData &headerData);

    /**
     * @brief Converts a stream of bytes to a header data
     * @param bytes the stream of bytes
     * @return the header data
     */
    static HeaderData BytesToHeaderData(const bytes &bytes);

    /**
     * @brief Converts a packet of data to a strea of bytes
     * @param packetData the packet data
     * @return the stream of bytes
     */
    static bytes PacketDataToBytes(const PacketData &packetData);

    /**
     * @brief Converts a stream of bytes to a packet data
     * @param bytes the stream of bytes
     * @return the packet data
     */
    static PacketData BytesToPacketData(const bytes &bytes);
};
} // namespace Networking::Message
