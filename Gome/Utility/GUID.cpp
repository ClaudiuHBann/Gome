#include "Gome/pch.h"

#include "GUID.h"

namespace Utility
{
GUID::GUID()
    : mStatus(::UuidCreate(&mUUID)), mIsGlobal(mStatus != RPC_S_UUID_LOCAL_ONLY),
      mIsGood(mStatus != RPC_S_UUID_NO_ADDRESS)
{
}

GUID::~GUID()
{
    Uninitialize();
}

GUID::GUID(const GUID &guid)
{
    *this = guid;
}

GUID &GUID::operator=(const GUID &right)
{
    Uninitialize();

    mUUID = right.mUUID;
    mStatus = RPC_S_OK;
    mIsGood = right.mIsGood;
    mIsGlobal = right.mIsGlobal;

    return *this;
}

void GUID::SetUUID(const ::UUID &uuid)
{
    Uninitialize();

    mUUID = uuid;
    mStatus = RPC_S_OK;
    mIsGood = true;
    mIsGlobal = false;
}

GUID::RPC_STR GUID::GetStr()
{
    if (!mUUIDString)
    {
        mStatus = ::UuidToString(&mUUID, &mUUIDString);
    }

    return mStatus == RPC_S_OK ? mUUIDString : mUUIDStringDefault;
}

const ::UUID &GUID::GetUUID() const
{
    return mIsGood ? mUUID : mUUIDDefault;
}

void GUID::Uninitialize()
{
    if (mUUIDString)
    {
        ::RpcStringFree(&mUUIDString);
        mUUIDString = nullptr;
    }
}

bool GUID::operator==(const GUID &right) const
{
    return mUUID == right.mUUID;
}

bool GUID::operator!=(const GUID &right) const
{
    return !(*this == right);
}
} // namespace Utility
