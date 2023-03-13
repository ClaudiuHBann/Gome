#include "pch.h"
#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			PacketMetadata::PacketMetadata(const HeaderMetadata& headerMetadata)
				: mHeaderMetadata(headerMetadata) {
			}

			PacketData::PacketData(const HeaderData& headerData, const wstring& content)
				: mHeaderData(headerData) {
				assert(content.length() <= CONTENT_SIZE_MAX);
				mContent = content;
			}
		}
	}
}
