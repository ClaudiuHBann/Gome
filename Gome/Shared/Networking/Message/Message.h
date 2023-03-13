#pragma once

#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class MessageManager;
			class MessageConverter;

			class Message {
				friend class MessageManager;
				friend class MessageConverter;

				Message(const PacketMetadata& packetMetadata);

				PacketMetadata mPacketMetadata;
				vector<PacketData> mPacketDatas;
			};
		}
	}
}
