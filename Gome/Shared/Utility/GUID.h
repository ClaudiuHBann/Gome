#pragma once

namespace Shared {
	namespace Utility {
		class GUID {
		public:
			static const size_t GUID_SIZE = 16;

			GUID();
			~GUID();

			bool IsGlobal() const;

			const ::RPC_WSTR& GetStr();
			wstring GetString();

			const ::UUID& GetUUID() const;
			void SetUUID(const ::UUID& uuid);

		private:
			bool IsGood() const;

			::UUID mUUID {};
			static inline ::UUID mUUIDDefault {};

			::RPC_WSTR mUUIDString {};
			static inline ::RPC_WSTR mUUIDStringDefault = (::RPC_WSTR)TEXT("");

			::RPC_STATUS mStatus {};
			bool mIsGlobal {};
			bool mUUIDStringTryCreate {};
		};
	}
}