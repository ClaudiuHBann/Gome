#include "Gome/pch.h"
#include "Header.h"
#include "Packet.h"

namespace Shared::Networking::Message {
	using namespace Utility;

	HeaderMetadata::HeaderMetadata(const Utility::GUID& guid, const Type type, const size_t size)
		: mGUID(guid), mSize(size) {
		assert(Type::NONE < type&& type < Type::COUNT);
		mType = type;
	}

	wstring HeaderMetadata::TypeToString() const {
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

		headerAsString += reinterpret_cast<const wchar_t*>(mGUID.GetStr());
		headerAsString += L"|";
		headerAsString += TypeToString();
		headerAsString += L"|";
		headerAsString += to_wstring(mSize);

		return headerAsString;
	}

	const Utility::GUID& HeaderMetadata::GetGUID() const {
		return mGUID;
	}

	const HeaderMetadata::Type& HeaderMetadata::GetType() const {
		return mType;
	}

	const size_t& HeaderMetadata::GetSize() const {
		return mSize;
	}

	HeaderData::HeaderData(const Utility::GUID& guid, const size_t index)
		: mGUID(guid), mIndex(index) {
	}

	wstring HeaderData::ToString() {
		wstring headerAsString;

		headerAsString += reinterpret_cast<const wchar_t*>(mGUID.GetStr());
		headerAsString += L"|";
		headerAsString += to_wstring(mIndex);

		return headerAsString;
	}

	const Utility::GUID& HeaderData::GetGUID() const {
		return mGUID;
	}

	const size_t& HeaderData::GetIndex() const {
		return mIndex;
	}
}
