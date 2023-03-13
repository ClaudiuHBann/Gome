#include "pch.h"
#include "MessageManager.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			Message MessageManager::ToMessage(const wstring& data, HeaderMetadata::Type type, Utility::GUID guid /* = {} */) const {
				HeaderMetadata headerMetadata(guid, type, data.length());
				PacketMetadata packetMetadata(headerMetadata);

				Message message(packetMetadata);

				auto packetsCount = data.length() / PacketData::CONTENT_SIZE_MAX;
				for (size_t i = 0; i < packetsCount; i++) {
					HeaderData headerData(guid, i);
					auto&& content(data.substr(i * PacketData::CONTENT_SIZE_MAX, (i + 1) * PacketData::CONTENT_SIZE_MAX));
					PacketData packetData(headerData, content);

					message.mPacketDatas.push_back(packetData);
				}

				auto packetLastSize = data.length() % PacketData::CONTENT_SIZE_MAX;
				if (packetLastSize) {
					packetsCount++;

					HeaderData headerData(guid, packetsCount);
					auto&& content(data.substr(packetsCount * PacketData::CONTENT_SIZE_MAX));
					PacketData packetData(headerData, content);

					message.mPacketDatas.push_back(packetData);
				}

				return message;
			}

			tuple<Utility::GUID, HeaderMetadata::Type, wstring> MessageManager::FromMessage(const Message& message) const {
				return tuple<Utility::GUID, HeaderMetadata::Type, wstring>();
			}
		}
	}
}
