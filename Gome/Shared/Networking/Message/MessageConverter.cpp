#include "Gome/pch.h"
#include "MessageConverter.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			using namespace Utility;

			/* static */ MessageConverter::bytes MessageConverter::MessageToBytes(const Message& message) {
				auto&& bytes = PacketMetadataToBytes(message.mPacketMetadata);
				auto&& bytesPacketDatas = PacketDatasToBytes(message.mPacketDatas);
				bytes.append_range(bytesPacketDatas);

				return bytes;
			}

			/* static */ Message MessageConverter::BytesToMessage(const bytes& bytes) {
				MessageConverter::bytes packetMetadataAsBytes(bytes.begin(), bytes.begin() + HeaderMetadata::SIZE);

				auto&& packetMetadata = BytesToPacketMetadata(packetMetadataAsBytes);
				Message message(packetMetadata);

				MessageConverter::bytes packetDatasAsBytes(bytes.begin() + HeaderMetadata::SIZE, bytes.end());
				message.mPacketDatas = move(BytesToPacketDatas(packetDatasAsBytes));

				return message;
			}

			/* static */ MessageConverter::bytes MessageConverter::PacketMetadataToBytes(const PacketMetadata& packetMetadata) {
				return HeaderMetadataToBytes(packetMetadata.GetHeaderMetadata());
			}

			/* static */ MessageConverter::bytes MessageConverter::PacketDataToBytes(const PacketData& packetData) {
				auto&& bytes(HeaderDataToBytes(packetData.GetHeaderData()));
				bytes.append_range(packetData.GetContent());

				return bytes;
			}

			/* static */ PacketData MessageConverter::BytesToPacketData(const bytes& bytes) {
				assert(bytes.size() <= PacketData::SIZE);

				MessageConverter::bytes headerAsBytes(bytes.begin(), bytes.begin() + HeaderData::SIZE);
				auto&& header = BytesToHeaderData(headerAsBytes);

				MessageConverter::bytes contentAsBytes(bytes.begin() + HeaderData::SIZE, bytes.end());

				return PacketData(header, contentAsBytes);
			}

			/* static */ vector<PacketData> MessageConverter::BytesToPacketDatas(const bytes& bytes) {
				vector<PacketData> packetDatas;

				auto packetDatasCount = bytes.size() / PacketData::SIZE;
				for (size_t i = 0; i < packetDatasCount; i++) {
					MessageConverter::bytes packetDataAsBytes(bytes.begin() + i * PacketData::SIZE, bytes.begin() + (i + 1) * PacketData::SIZE);
					packetDatas.push_back(BytesToPacketData(packetDataAsBytes));
				}

				auto packetDatasLastSize = bytes.size() % PacketData::SIZE;
				if (packetDatasLastSize) {
					MessageConverter::bytes packetDataAsBytes(bytes.begin() + packetDatasCount * PacketData::SIZE, bytes.begin() + packetDatasCount * PacketData::SIZE + packetDatasLastSize);
					packetDatas.push_back(BytesToPacketData(packetDataAsBytes));
				}

				return packetDatas;
			}

			/* static */ PacketMetadata MessageConverter::BytesToPacketMetadata(const bytes& bytes) {
				return BytesToHeaderMetadata(bytes);
			}

			/* static */ MessageConverter::bytes MessageConverter::PacketDatasToBytes(const vector<PacketData>& packetDatas) {
				bytes bytes;

				for (const auto& packetData : packetDatas) {
					bytes.append_range(PacketDataToBytes(packetData));
				}

				return bytes;
			}

			/* static */ MessageConverter::bytes MessageConverter::HeaderMetadataToBytes(const HeaderMetadata& headerMetadata) {
				bytes headerAsBytes;

				auto guidRawAsBytePtr = (byte*)&headerMetadata.GetGUID().GetUUID();
				bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + GUID::GUID_SIZE);
				headerAsBytes.append_range(guidRawAsBytes);

				headerAsBytes.push_back((byte)headerMetadata.GetType());

				auto sizeAsBytePtr = (byte*)&headerMetadata.GetSize();
				bytes sizeAsBytes(sizeAsBytePtr, sizeAsBytePtr + sizeof(headerMetadata.GetSize()));
				headerAsBytes.append_range(sizeAsBytes);

				return headerAsBytes;
			}

			/* static */ HeaderMetadata MessageConverter::BytesToHeaderMetadata(const bytes& bytes) {
				assert(bytes.size() == HeaderMetadata::SIZE);

				MessageConverter::bytes guidAsBytes(bytes.begin(), bytes.begin() + GUID::GUID_SIZE);
				Utility::GUID guid;
				guid.SetUUID(*reinterpret_cast<UUID*>(guidAsBytes.data()));
				assert(guid.GetStr());

				auto type = (HeaderMetadata::Type)bytes[GUID::GUID_SIZE];
				assert(HeaderMetadata::Type::NONE < type&& type < HeaderMetadata::Type::COUNT);

				HeaderMetadata::bytes sizeAsBytes(bytes.begin() + GUID::GUID_SIZE + sizeof(HeaderMetadata::Type), bytes.begin() + HeaderMetadata::SIZE);
				auto size = *reinterpret_cast<size_t*>(sizeAsBytes.data());

				return HeaderMetadata(guid, type, size);
			}

			/* static */ MessageConverter::bytes MessageConverter::HeaderDataToBytes(const HeaderData& headerData) {
				bytes headerAsBytes;

				auto guidRawAsBytePtr = (byte*)&headerData.GetGUID().GetUUID();
				bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + GUID::GUID_SIZE);
				headerAsBytes.append_range(guidRawAsBytes);

				auto indexValidAsBytePtr = (byte*)&headerData.GetIndex();
				bytes indexValidAsBytes(indexValidAsBytePtr, indexValidAsBytePtr + sizeof(headerData.GetIndex()));
				headerAsBytes.append_range(indexValidAsBytes);

				return headerAsBytes;
			}

			/* static */ HeaderData MessageConverter::BytesToHeaderData(const bytes& bytes) {
				assert(bytes.size() == HeaderData::SIZE);

				MessageConverter::bytes guidAsBytes(bytes.begin(), bytes.begin() + GUID::GUID_SIZE);
				Utility::GUID guid;
				guid.SetUUID(*reinterpret_cast<UUID*>(guidAsBytes.data()));
				assert(guid.GetStr());

				HeaderMetadata::bytes indexAsBytes(bytes.begin() + GUID::GUID_SIZE, bytes.begin() + HeaderData::SIZE);
				auto index = *reinterpret_cast<size_t*>(indexAsBytes.data());

				return HeaderData(guid, index);
			}
		}
	}
}