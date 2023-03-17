#pragma once

namespace Shared::Utility
{
class GUID
{
#if defined(UNICODE) || defined(_UNICODE)
    using RPC_STR = ::RPC_WSTR;
#else
    using RPC_STR = ::RPC_CSTR;
#endif // defined(UNICODE) || defined(_UNICODE)

  public:
    static const size_t GUID_SIZE = 16;

    GUID();
    ~GUID();

    GUID(const GUID &guid);
    GUID &operator=(const GUID &right);

    bool operator==(const GUID &right);

    bool IsGlobal() const;
    bool IsGood() const;

    void SetUUID(const ::UUID &uuid);
    void SetUUID(RPC_STR uuidStr);

    RPC_STR GetStr();
    const ::UUID &GetUUID() const;
    ::RPC_STATUS GetStatus() const;

  private:
    void Uninitialize();

    ::UUID mUUID{};
    static inline ::UUID mUUIDDefault{};

    RPC_STR mUUIDString{};
    static inline RPC_STR mUUIDStringDefault = (RPC_STR)TEXT("");

    ::RPC_STATUS mStatus{};
    bool mIsGood{};
    bool mIsGlobal{};
};
} // namespace Shared::Utility
