#include "pch.h"
#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			Packet::Packet(const Header& header, const wstring& content)
				: mHeader(header) {
				assert(content.length() <= CONTENT_SIZE_MAX);
				mContent = content;
			}
		}
	}
}
