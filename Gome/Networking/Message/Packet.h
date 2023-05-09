#pragma once

#include "Header.h"

namespace Networking::Message
{
/**
 * @brief The metadata of a packet of data
 */
class PacketMetadata
{
  public:
    /**
     * @brief Constructor
     * @param headerMetadata the metadata of a header
     */
    PacketMetadata(const HeaderMetadata &headerMetadata);

    /**
     * @brief Gets the header's metadata
     * @return header's metadata
     */
    const HeaderMetadata &GetHeaderMetadata() const;

    /**
     * @brief == operator overload
     * @param right the object to check for equality
     * @return true if objets are equal or false otherwise
     */
    bool operator==(const PacketMetadata &right);

  private:
    HeaderMetadata mHeaderMetadata;
};

/**
 * @brief The data of a packet
 */
class PacketData
{
  public:
    using bytes = vector<byte>;

    /**
     * @brief The maximum size of a packet of data
     */
    static const size_t SIZE = 8192;

    /**
     * @brief The maximum size of the context of the packet of data
     */
    static const size_t CONTENT_SIZE_MAX = SIZE - HeaderData::SIZE;

    /**
     * @brief Constructor
     * @param headerMetadata the metadata of the header
     * @param content the content of the packet of data
     */
    PacketData(const HeaderData &headerData, const bytes &content);

    const HeaderData &GetHeaderData() const;
    const bytes &GetContent() const;

    const size_t GetSize() const;

    bool operator==(const PacketData &right);

  private:
    HeaderData mHeaderData;
    bytes mContent{};
};
} // namespace Networking::Message
