#pragma once

#include "Shared/Utility/GUID.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class HeaderMetadata {
			public:
				using bytes = vector<byte>;

				enum class Type : uint8_t {
					NONE,
					PING,
					TEXT,
					COUNT
				};

				static const size_t HEADER_METADATA_SIZE = Utility::GUID::GUID_SIZE + sizeof(Type) + sizeof(size_t);

				HeaderMetadata(const bytes& header);
				HeaderMetadata(const Utility::GUID& guid, const Type type, const size_t size);

				bytes ToBytes();
				wstring ToString();

			private:
				Utility::GUID mGUID {};
				Type mType = Type::NONE;
				size_t mSize {};

				wstring TypeToString();
			};

			class HeaderData {
			public:
				using bytes = vector<byte>;

				static const size_t HEADER_DATA_SIZE = Utility::GUID::GUID_SIZE + sizeof(size_t);

				HeaderData(const bytes& header);
				HeaderData(const Utility::GUID& guid, const size_t index);

				bytes ToBytes();
				wstring ToString();

			private:
				Utility::GUID mGUID {};
				size_t mIndex {};
			};
		}
	}
}
