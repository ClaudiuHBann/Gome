#include "Gome/pch.h"

#include "GUID.h"

namespace Utility
{
using namespace uuids;

GUID::GUID() : mUUID(uuid_system_generator{}())
{
}

GUID::GUID(const bytes &guid) : mUUID(guid.begin(), guid.end())
{
}

string GUID::GetStr()
{
    return to_string(mUUID);
}

const uuid &GUID::GetUUID() const
{
    return mUUID;
}
} // namespace Utility
