#include "pch.h"
#include "Header.h"
#include "Message.h"
#include <iostream>

namespace Shared {
	namespace Message {
		using namespace Utility;

		Header::Header(const Type type, const size_t bufferValid) {
			assert(Type::NONE < type&& type < Type::COUNT);
			mType = type;

			assert(bufferValid <= Message::CONTENT_SIZE_MAX);
			mBufferValid = bufferValid;
		}

		Header::Header(const bytes& header) {
			assert(header.size() == HEADER_SIZE);

			bytes guid(header.begin(), header.begin() + GUID::GUID_SIZE);
			mGUID.SetUUID(*reinterpret_cast<UUID*>(guid.data()));
			assert(!mGUID.GetString().empty());

			mType = (Type)header[GUID::GUID_SIZE];
			assert(Type::NONE < mType&& mType < Type::COUNT);

			bytes bufferValid(header.begin() + GUID::GUID_SIZE + sizeof(Type), header.begin() + HEADER_SIZE);
			mBufferValid = *reinterpret_cast<size_t*>(bufferValid.data());
			assert(mBufferValid <= Message::CONTENT_SIZE_MAX);
		}

		Header::bytes Header::ToBytes() {
			bytes headerAsBytes;

			auto guidRawAsBytePtr = (byte*)&mGUID.GetUUID();
			bytes guidRawAsBytes(guidRawAsBytePtr, guidRawAsBytePtr + GUID::GUID_SIZE);
			headerAsBytes.append_range(guidRawAsBytes);

			headerAsBytes.push_back((byte)mType);

			auto bufferValidAsBytePtr = reinterpret_cast<byte*>(&mBufferValid);
			bytes bufferValidAsBytes(bufferValidAsBytePtr, bufferValidAsBytePtr + sizeof(mBufferValid));
			headerAsBytes.append_range(bufferValidAsBytes);

			return headerAsBytes;
		}

		wstring Header::TypeToString() {
			switch (mType) {
			case Type::PING:
				return L"PING";
			case Type::TEXT:
				return L"TEXT";
			}

			return L"";
		}

		wstring Header::ToString() {
			wstring headerAsString;

			headerAsString += mGUID.GetString();
			headerAsString += L"|";
			headerAsString += TypeToString();
			headerAsString += L"|";
			headerAsString += to_wstring(mBufferValid);

			return headerAsString;
		}
	}
}