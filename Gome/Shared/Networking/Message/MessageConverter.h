#pragma once

#include "Message.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class MessageConverter {
			public:
				using bytes = vector<byte>;

				static bytes MessageToBytes(const Message& message);
				static Message BytesToMessage(const bytes& bytes);

				static bytes PacketMetadataToBytes(const PacketMetadata& packetMetadata);
				static PacketMetadata BytesToPacketMetadata(const bytes& bytes);

				static bytes PacketDatasToBytes(const vector<PacketData>& packetDatas);
				static vector<PacketData> BytesToPacketDatas(const bytes& bytes);

				static bytes HeaderMetadataToBytes(const HeaderMetadata& headerMetadata);
				static HeaderMetadata BytesToHeaderMetadata(const bytes& bytes);

				static bytes HeaderDataToBytes(const HeaderData& headerData);
				static HeaderData BytesToHeaderData(const bytes& bytes);

			private:
				static bytes PacketDataToBytes(const PacketData& packetData);
				static PacketData BytesToPacketData(const bytes& bytes);
			};
		}
	}
}
