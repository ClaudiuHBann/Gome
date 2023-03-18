#pragma once

#include "Message.h"

namespace Shared::Networking::Message
{
class MessageManager
{
  public:
    using bytes = vector<byte>;
    using MessageDisassembled = tuple<Utility::GUID, HeaderMetadata::Type, bytes>;

    static Message ToMessage(const bytes &bytes, HeaderMetadata::Type type, Utility::GUID guid = {});
    static MessageDisassembled FromMessage(const Message &message);
};
} // namespace Shared::Networking::Message
