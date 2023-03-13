#include "pch.h"
#include "Header.h"
#include "Packet.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			using namespace Utility;

			HeaderMetadata::HeaderMetadata(const Utility::GUID& guid, const Type type, const size_t size)
				: mGUID(guid), mSize(size) {
				assert(Type::NONE < type&& type < Type::COUNT);
				mType = type;
			}

			HeaderMetadata::HeaderMetadata(const bytes& header) {
				assert(header.size() == HEADER_METADATA_SIZE);

				bytes guid(header.begin(), header.begin() + GUID::GUID_SIZE);
				mGUID.SetUUID(*reinterpret_cast<UUID*>(guid.data()));
				assert(!mGUID.GetString().empty());

				mType = (Type)header[GUID::GUID_SIZE];
				assert(Type::NONE < mType&& mType < Type::COUNT);

				bytes size(header.begin() + GUID::GUID_SIZE + sizeof(Type), header.begin() + HEADER_METADATA_SIZE);
				mSize = *reinterpret_cast<size_t*>(size.data());
			}

			HeaderMetadata::bytes HeaderMetadata::ToBytes() {
				bytes headerAsBytes;

				auto guidRawAsBytePtr = (byte*)&mGUID.GetUUID();
				bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + GUID::GUID_SIZE);
				headerAsBytes.append_range(guidRawAsBytes);

				headerAsBytes.push_back((byte)mType);

				auto sizeAsBytePtr = reinterpret_cast<byte*>(&mSize);
				bytes sizeAsBytes(sizeAsBytePtr, sizeAsBytePtr + sizeof(mSize));
				headerAsBytes.append_range(sizeAsBytes);

				return headerAsBytes;
			}

			wstring HeaderMetadata::TypeToString() {
				switch (mType) {
				case Type::PING:
					return L"PING";
				case Type::TEXT:
					return L"TEXT";
				}

				return L"";
			}

			wstring HeaderMetadata::ToString() {
				wstring headerAsString;

				headerAsString += mGUID.GetString();
				headerAsString += L"|";
				headerAsString += TypeToString();
				headerAsString += L"|";
				headerAsString += to_wstring(mSize);

				return headerAsString;
			}

			HeaderData::HeaderData(const bytes& header) {
				assert(header.size() == HEADER_DATA_SIZE);

				bytes guid(header.begin(), header.begin() + GUID::GUID_SIZE);
				mGUID.SetUUID(*reinterpret_cast<UUID*>(guid.data()));
				assert(!mGUID.GetString().empty());

				bytes index(header.begin() + GUID::GUID_SIZE, header.begin() + HEADER_DATA_SIZE);
				mIndex = *reinterpret_cast<size_t*>(index.data());
			}

			HeaderData::HeaderData(const Utility::GUID& guid, const size_t index)
				: mGUID(guid), mIndex(index) {
			}

			HeaderData::bytes HeaderData::ToBytes() {
				bytes headerAsBytes;

				auto guidRawAsBytePtr = (byte*)&mGUID.GetUUID();
				bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + GUID::GUID_SIZE);
				headerAsBytes.append_range(guidRawAsBytes);

				auto indexValidAsBytePtr = reinterpret_cast<byte*>(&mIndex);
				bytes indexValidAsBytes(indexValidAsBytePtr, indexValidAsBytePtr + sizeof(mIndex));
				headerAsBytes.append_range(indexValidAsBytes);

				return headerAsBytes;
			}

			wstring HeaderData::ToString() {
				wstring headerAsString;

				headerAsString += mGUID.GetString();
				headerAsString += L"|";
				headerAsString += to_wstring(mIndex);

				return headerAsString;
			}
		}
	}
}
