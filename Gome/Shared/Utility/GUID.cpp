#include "Gome/pch.h"
#include "GUID.h"

namespace Shared {
	namespace Utility {
		GUID::GUID()
			: mStatus(::UuidCreate(&mUUID)),
			mIsGlobal(mStatus != RPC_S_UUID_LOCAL_ONLY) {
		}

		GUID::GUID(const GUID& guid) {
			*this = guid;
		}

		GUID& GUID::operator=(const GUID& right) {
			mUUID = right.mUUID;
			mIsGlobal = right.mIsGlobal;
			mStatus = ::UuidToString(&mUUID, &mUUIDString);
			mUUIDStringTryCreate = true;

			return *this;
		}

		GUID::~GUID() {
			Uninitialize();
		}

		bool GUID::IsGlobal() const {
			return mIsGlobal;
		}

		const GUID::RPC_STR& GUID::GetStr() {
			if (!mUUIDString && IsGood()) {
				mStatus = ::UuidToString(&mUUID, &mUUIDString);
				mUUIDStringTryCreate = true;
			}

			return IsGood() ? mUUIDString : mUUIDStringDefault;
		}

		const ::UUID& GUID::GetUUID() const {
			return IsGood() ? mUUID : mUUIDDefault;
		}

		void GUID::SetUUID(const ::UUID& uuid) {
			Reset();

			mUUID = uuid;
		}

		void GUID::Uninitialize() {
			if (mUUIDString && IsGood()) {
				::RpcStringFree(&mUUIDString);
				mUUIDString = nullptr;
			}
		}

		void GUID::Reset() {
			Uninitialize();

			mStatus = RPC_S_OK;
			mIsGlobal = false;
			mUUIDStringTryCreate = false;
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