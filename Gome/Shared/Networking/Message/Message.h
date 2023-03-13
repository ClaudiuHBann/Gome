#pragma once

#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class MessageManager;

			class Message {
				friend class MessageManager;

				Message(const PacketMetadata& packetMetadata);

				PacketMetadata mPacketMetadata;
				vector<PacketData> mPacketDatas;
			};
		}
	}
}
