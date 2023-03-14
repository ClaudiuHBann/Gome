#pragma once

#include "Header.h"

namespace Shared::Networking::Message {
	class PacketMetadata {
	public:
		PacketMetadata(const HeaderMetadata& headerMetadata);

		const HeaderMetadata& GetHeaderMetadata() const;

		bool operator==(const PacketMetadata& right);

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

		bool operator==(const PacketData& right);

	private:
		HeaderData mHeaderData;
		bytes mContent {};
	};
}
