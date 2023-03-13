#pragma once

namespace Shared {
	namespace Utility {
		class GUID {
#ifdef UNICODE
			typedef ::RPC_WSTR RPC_STR;
#else
			typedef ::RPC_CSTR RPC_STR;
#endif // UNICODE

		public:
			static const size_t GUID_SIZE = 16;

			GUID();
			GUID(const GUID& guid);
			~GUID();

			bool IsGlobal() const;

			const RPC_STR& GetStr();

			const ::UUID& GetUUID() const;
			void SetUUID(const ::UUID& uuid);

			GUID& operator=(const GUID& right);

		private:
			bool IsGood() const;

			void Uninitialize();
			void Reset();

			::UUID mUUID {};
			static inline ::UUID mUUIDDefault {};

			RPC_STR mUUIDString {};
			static inline RPC_STR mUUIDStringDefault = (RPC_STR)TEXT("");

			::RPC_STATUS mStatus {};
			bool mIsGlobal {};
			bool mUUIDStringTryCreate {};
		};
	}
}