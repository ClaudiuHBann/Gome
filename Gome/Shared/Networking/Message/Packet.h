#pragma once

#include "Header.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class PacketMetadata {
			public:
				PacketMetadata(const HeaderMetadata& headerMetadata);

			private:
				HeaderMetadata mHeaderMetadata;
			};

			class PacketData {
			public:
				static const size_t CONTENT_SIZE_MAX = 8192 - HeaderData::HEADER_DATA_SIZE;

				PacketData(const HeaderData& headerData, const wstring& content);

			private:
				HeaderData mHeaderData;
				wstring mContent {};
			};
		}
	}
}
