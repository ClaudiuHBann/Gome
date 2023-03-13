#include "Gome/pch.h"
#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			PacketMetadata::PacketMetadata(const HeaderMetadata& headerMetadata)
				: mHeaderMetadata(headerMetadata) {
			}

			const HeaderMetadata& PacketMetadata::GetHeaderMetadata() const {
				return mHeaderMetadata;
			}

			PacketData::PacketData(const HeaderData& headerData, const bytes& content)
				: mHeaderData(headerData) {
				assert(content.size() <= CONTENT_SIZE_MAX);
				mContent = content;
			}

			const HeaderData& PacketData::GetHeaderData() const {
				return mHeaderData;
			}

			const PacketData::bytes& PacketData::GetContent() const {
				return mContent;
			}
		}
	}
}
