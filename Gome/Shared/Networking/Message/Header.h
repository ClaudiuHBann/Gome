#pragma once

#include "Shared/Utility/GUID.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class Header {
			public:
				using bytes = vector<byte>;

				enum class Type : uint8_t {
					NONE,
					PING,
					TEXT,
					COUNT
				};

				static const size_t HEADER_SIZE = Utility::GUID::GUID_SIZE + sizeof(Type) + sizeof(size_t);

				Header(const bytes& header);
				Header(const Type type, const size_t bufferValid);

				bytes ToBytes();
				wstring ToString();

			private:
				Utility::GUID mGUID {};
				Type mType = Type::NONE;
				size_t mBufferValid {};

				wstring TypeToString();
			};
		}
	}
}
