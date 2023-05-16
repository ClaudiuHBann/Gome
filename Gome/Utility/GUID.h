#pragma once

#include "Gome/uuid.hpp"

namespace Utility
{
using namespace uuids;

/**
 * @brief Wrapper for Marius Bancila's stduuid
 */
class GUID
{
  public:
    /**
     * @brief GUID size in bytes
     */
    static const size_t GUID_SIZE = 16;

    /**
     * @brief Constructor
     */
    GUID();

    /**
     * @brief Constructor
     * @param guid as bytes
     */
    GUID(const bytes &guid);

    /**
     * @brief Gets the GUID as a string
     * @return the guid as a string
     */
    string GetStr();

    /**
     * @brief Gets the UUID of the GUID
     * @return the uuid
     */
    const uuid &GetUUID() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const GUID &) const = default;

  private:
    uuid mUUID{};
};
} // namespace Utility
