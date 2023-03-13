#include "Gome/pch.h"
#include "MessageManager.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			/* static */ Message MessageManager::ToMessage(const bytes& bytes, HeaderMetadata::Type type, Utility::GUID guid /* = {} */) {
				HeaderMetadata headerMetadata(guid, type, bytes.size());
				PacketMetadata packetMetadata(headerMetadata);

				Message message(packetMetadata);

				auto packetsCount = bytes.size() / PacketData::CONTENT_SIZE_MAX;
				for (size_t i = 0; i < packetsCount; i++) {
					HeaderData headerData(guid, i);
					MessageManager::bytes content(bytes.begin() + i * PacketData::CONTENT_SIZE_MAX, bytes.begin() + (i + 1) * PacketData::CONTENT_SIZE_MAX);
					PacketData packetData(headerData, content);

					message.mPacketDatas.push_back(packetData);
				}

				auto packetLastSize = bytes.size() % PacketData::CONTENT_SIZE_MAX;
				if (packetLastSize) {
					packetsCount++;

					HeaderData headerData(guid, packetsCount);
					MessageManager::bytes content(bytes.begin() + packetsCount * PacketData::CONTENT_SIZE_MAX, bytes.begin() + packetsCount * PacketData::CONTENT_SIZE_MAX + packetLastSize);
					PacketData packetData(headerData, content);

					message.mPacketDatas.push_back(packetData);
				}

				return message;
			}

			/* static */ tuple<Utility::GUID, HeaderMetadata::Type, MessageManager::bytes> MessageManager::FromMessage(const Message& message) {
				bytes bytes(message.mPacketMetadata.GetHeaderMetadata().GetSize());

				for (const auto& packetData : message.mPacketDatas) {
					bytes.insert_range(bytes.begin() + packetData.GetHeaderData().GetIndex() * PacketData::CONTENT_SIZE_MAX, packetData.GetContent());
				}

				return {
					message.mPacketMetadata.GetHeaderMetadata().GetGUID(),
					message.mPacketMetadata.GetHeaderMetadata().GetType(),
					bytes
				};
			}
		}
	}
}
