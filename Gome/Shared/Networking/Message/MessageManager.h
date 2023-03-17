#pragma once

#include "Message.h"

namespace Shared::Networking::Message
{
class MessageManager
{
  public:
    using bytes = vector<byte>;

    static Message ToMessage(const bytes &bytes, HeaderMetadata::Type type, Utility::GUID guid = {});
    static tuple<Utility::GUID, HeaderMetadata::Type, bytes> FromMessage(const Message &message);
};
} // namespace Shared::Networking::Message
