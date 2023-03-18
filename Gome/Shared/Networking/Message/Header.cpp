#include "Gome/pch.h"
//
#include "Header.h"
//
#include "Packet.h"

namespace Shared::Networking::Message
{
using namespace Utility;

constexpr auto HEADER_METADATA_TYPE_STRING_PING = TEXT("PING");

constexpr auto HEADER_STRING_DELIMITATOR = TEXT("|");

HeaderMetadata::HeaderMetadata(const Utility::GUID &guid, const Type type, const size_t size) : mGUID(guid), mSize(size)
{
    assert(Type::NONE < type && type < Type::COUNT);
    mType = type;
}

String HeaderMetadata::TypeToString() const
{
    switch (mType)
    {
    case Type::PING:
        return HEADER_METADATA_TYPE_STRING_PING;
    }

    return {};
}

String HeaderMetadata::ToString()
{
    String headerAsString;

    headerAsString += reinterpret_cast<const ::TCHAR *>(mGUID.GetStr());
    headerAsString += HEADER_STRING_DELIMITATOR;
    headerAsString += TypeToString();
    headerAsString += HEADER_STRING_DELIMITATOR;
    headerAsString += Utility::ToString(mSize);

    return headerAsString;
}

const Utility::GUID &HeaderMetadata::GetGUID() const
{
    return mGUID;
}

const HeaderMetadata::Type &HeaderMetadata::GetType() const
{
    return mType;
}

const size_t &HeaderMetadata::GetSize() const
{
    return mSize;
}

HeaderData::HeaderData(const Utility::GUID &guid, const size_t index) : mGUID(guid), mIndex(index)
{
}

String HeaderData::ToString()
{
    String headerAsString;

    headerAsString += reinterpret_cast<const ::TCHAR *>(mGUID.GetStr());
    headerAsString += HEADER_STRING_DELIMITATOR;
    headerAsString += Utility::ToString(mIndex);

    return headerAsString;
}

const Utility::GUID &HeaderData::GetGUID() const
{
    return mGUID;
}

const size_t &HeaderData::GetIndex() const
{
    return mIndex;
}
} // namespace Shared::Networking::Message
