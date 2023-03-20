#pragma once

#include "Gome/Utility/GUID.h"
#include "Gome/Utility/String.h"

namespace Networking::Message
{
using namespace Utility;

class HeaderMetadata
{
  public:
    using bytes = vector<byte>;

    enum class Type : uint8_t
    {
        NONE,
        PING,
        TEXT,
        COUNT
    };

    static const size_t SIZE = Utility::GUID::GUID_SIZE + sizeof(Type) + sizeof(size_t);

    HeaderMetadata(const Utility::GUID &guid, const Type type, const size_t size);

    const Utility::GUID &GetGUID() const;
    const Type &GetType() const;
    const size_t &GetSize() const;

    String ToString();

    bool operator==(const auto &right)
    {
        return this->mGUID.GetUUID() == right.mGUID.GetUUID() && this->mType == right.mType &&
               this->mSize == right.mSize;
    }

  private:
    Utility::GUID mGUID{};
    Type mType = Type::NONE;
    size_t mSize{};

    String TypeToString() const;
};

class HeaderData
{
  public:
    using bytes = vector<byte>;

    static const size_t SIZE = Utility::GUID::GUID_SIZE + sizeof(size_t);

    HeaderData(const Utility::GUID &guid, const size_t index);

    const Utility::GUID &GetGUID() const;
    const size_t &GetIndex() const;

    String ToString();

    bool operator==(const auto &right)
    {
        return this->mGUID.GetUUID() == right.mGUID.GetUUID() && this->mIndex == right.mIndex;
    }

  private:
    Utility::GUID mGUID{};
    size_t mIndex{};
};
} // namespace Networking::Message