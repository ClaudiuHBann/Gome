#include "Gome/pch.h"
#include "Message.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			Message::Message(const PacketMetadata& packetMetadata)
				: mPacketMetadata(packetMetadata) {
			}

		}
	}
}
