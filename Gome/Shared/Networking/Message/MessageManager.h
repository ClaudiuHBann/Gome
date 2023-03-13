#pragma once

#include "Message.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class MessageManager {
			public:
				Message ToMessage(const wstring& data, HeaderMetadata::Type type, Utility::GUID guid) const;
				tuple<Utility::GUID, HeaderMetadata::Type, wstring> FromMessage(const Message& message) const;
			};
		}
	}
}
