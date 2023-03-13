#pragma once

#include "Header.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class Packet {
			public:
				static const size_t CONTENT_SIZE_MAX = 8192 - Header::HEADER_SIZE;

				Packet(const Header& header, const wstring& content);

			private:
				Header mHeader;
				wstring mContent {};
			};
		}
	}
}
