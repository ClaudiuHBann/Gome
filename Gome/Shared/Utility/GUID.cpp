#include "pch.h"
#include "GUID.h"

namespace Shared {
	namespace Utility {
		GUID::GUID()
			: mStatus(::UuidCreate(&mUUID)),
			mIsGlobal(mStatus == RPC_S_UUID_LOCAL_ONLY) {
		}

		GUID::~GUID() {
			if (mUUIDString && IsGood()) {
				::RpcStringFree(&mUUIDString);
			}
		}

		bool GUID::IsGlobal() const {
			return mIsGlobal;
		}

		const ::RPC_WSTR& GUID::GetStr() {
			if (!mUUIDString && IsGood()) {
				mStatus = ::UuidToString(&mUUID, &mUUIDString);
				mUUIDStringTryCreate = true;
			}

			return IsGood() ? mUUIDString : mUUIDStringDefault;
		}

		wstring GUID::GetString() {
			return wstring(reinterpret_cast<const wchar_t*>(GetStr()));
		}

		const::UUID& GUID::GetUUID() const {
			return IsGood() ? mUUID : mUUIDDefault;
		}

		void GUID::SetUUID(const ::UUID& uuid) {
			mUUID = uuid;
		}

		bool GUID::IsGood() const {
			if (mUUIDStringTryCreate) {
				return mStatus != RPC_S_OUT_OF_MEMORY;
			} else {
				if (mIsGlobal) {
					return true;
				} else {
					return mStatus != RPC_S_UUID_NO_ADDRESS;
				}
			}
		}
	}
}