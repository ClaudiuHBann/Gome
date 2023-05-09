#pragma once

#include "Message.h"

namespace Networking::Message
{
/**
 * @brief The manager of messages that creates a message or takes the data out of one
 */
class MessageManager
{
  public:
    using MessageDisassembled = tuple<Utility::GUID, HeaderMetadata::Type, bytes>;

    /**
     * @brief Creates a message
     * @param bytes the stream of bytes for the message to hold
     * @param type the message's type
     * @param guid the message's guid
     * @return the message
     */
    static Message ToMessage(const bytes &bytes, HeaderMetadata::Type type, Utility::GUID guid = {});

    /**
     * @brief Takes the data out of a message
     * @param message the message
     * @return the message's data
     */
    static MessageDisassembled FromMessage(const Message &message);
};
} // namespace Networking::Message
