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
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const PacketMetadata &) const = default;

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

    /**
     * @brief Gets the header of the data
     * @return the data's header
     */
    const HeaderData &GetHeaderData() const;

    /**
     * @brief Gets the content of the data
     * @return the data's content
     */
    const bytes &GetContent() const;

    const size_t GetSize() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const PacketData &) const = default;

  private:
    HeaderData mHeaderData;
    bytes mContent{};
};
} // namespace Networking::Message
