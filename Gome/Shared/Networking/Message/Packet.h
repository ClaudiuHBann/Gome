#pragma once

#include "Header.h"

namespace Shared {
	namespace Networking {
		namespace Message {
			class PacketMetadata {
			public:
				PacketMetadata(const HeaderMetadata& headerMetadata);

				const HeaderMetadata& GetHeaderMetadata() const;

			private:
				HeaderMetadata mHeaderMetadata;
			};

			class PacketData {
			public:
				using bytes = vector<byte>;

				static const size_t SIZE = 8192;
				static const size_t CONTENT_SIZE_MAX = SIZE - HeaderData::SIZE;

				PacketData(const HeaderData& headerData, const bytes& content);

				const HeaderData& GetHeaderData() const;
				const bytes& GetContent() const;

			private:
				HeaderData mHeaderData;
				bytes mContent {};
			};
		}
	}
}
