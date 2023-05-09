#pragma once

#include "Gome/Utility/GUID.h"
#include "Gome/Utility/String.h"

namespace Networking::Message
{
using namespace Utility;

/**
 * @brief Header's metadata
 */
class HeaderMetadata
{
  public:
    /**
     * @brief The types of messages
     */
    enum class Type : uint8_t
    {
        NONE,
        PING,
        TEXT,
        COUNT
    };

    /**
     * @brief The size in bytes of the header's metadata
     */
    static const size_t SIZE = Utility::GUID::GUID_SIZE + sizeof(Type) + sizeof(size_t);

    /**
     * @brief Constructor
     * @param guid the guid of the message
     * @param type the type of the message
     * @param size the size of the message
     */
    HeaderMetadata(const Utility::GUID &guid, const Type type, const size_t size);

    /**
     * @brief Gets the GUID of the message
     * @return the message's GUID
     */
    const Utility::GUID &GetGUID() const;

    /**
     * @brief Gets the type of the message
     * @return the message's type
     */
    const Type &GetType() const;

    /**
     * @brief Gets the size of the message
     * @return the message's size
     */
    const size_t &GetSize() const;

    /**
     * @brief Gets the string representation of the object
     * @return the string representation of the object
     */
    String ToString();

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const HeaderMetadata &) const = default;

  private:
    Utility::GUID mGUID{};
    Type mType = Type::NONE;
    size_t mSize{};

    /**
     * @brief Gets the type of the message as string
     * @return the type of the message as string
     */
    String TypeToString() const;
};

/**
 * @brief The header's data
 */
class HeaderData
{
  public:
    /**
     * @brief The size of the header's data
     */
    static const size_t SIZE = Utility::GUID::GUID_SIZE + sizeof(size_t);

    /**
     * @brief Constructor
     * @param guid the guid of the packet of the message
     * @param index the index of the packet of the message
     */
    HeaderData(const Utility::GUID &guid, const size_t index);

    /**
     * @brief Gets the GUID of the packet of the message
     * @return the GUID of the packet of the message
     */
    const Utility::GUID &GetGUID() const;

    /**
     * @brief Gets the index of the packet of the message
     * @return the index of the packet of the message
     */
    const size_t &GetIndex() const;

    /**
     * @brief Gets the string representation of the object
     * @return the string representation of the object
     */
    String ToString();

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const HeaderData &) const = default;

  private:
    Utility::GUID mGUID{};
    size_t mIndex{};
};
} // namespace Networking::Message
