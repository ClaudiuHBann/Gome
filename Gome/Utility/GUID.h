#pragma once

namespace Utility
{
// TODO: don't expose window's API data types for the GUID manipulation

/**
 * @brief GUID class wrapper for windows's API
 */
class GUID
{
#if defined(UNICODE) || defined(_UNICODE)
    using RPC_STR = ::RPC_WSTR;
#else
    using RPC_STR = ::RPC_CSTR;
#endif // defined(UNICODE) || defined(_UNICODE)

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
     * @brief Destructor
     */
    ~GUID();

    /**
     * @brief Constructor
     * @note allocates a new GUID on heap
     * @param guid the GUID to be copied
     */
    GUID(const GUID &guid);

    /**
     * @brief = operator overload
     * @param right the GUID to be copied
     * @return the GUID
     */
    GUID &operator=(const GUID &right);

    /**
     * @brief Creates the GUID from the UUID
     * @param uuid the uuid
     */
    void SetUUID(const ::UUID &uuid);

    /**
     * @brief Gets the GUID as a string
     * @return the guid as a string
     */
    RPC_STR GetStr();

    /**
     * @brief Gets the UUID of the GUID
     * @return the uuid
     */
    const ::UUID &GetUUID() const;

    /**
     * @brief C++20 Magic for the comparison boilerplate
     */
    auto operator<=>(const GUID &) const = default;

  private:
    /**
     * @brief Frees the GUID internally lazy initialized string
     */
    void Uninitialize();

    ::UUID mUUID{};
    static inline ::UUID mUUIDDefault{};

    RPC_STR mUUIDString{};
    static inline RPC_STR mUUIDStringDefault = (RPC_STR)TEXT("");

    ::RPC_STATUS mStatus{};
    bool mIsGood{};
    bool mIsGlobal{};
};
} // namespace Utility
