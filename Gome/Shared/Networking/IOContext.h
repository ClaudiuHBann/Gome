#pragma once

namespace Shared::Networking {
	class IOContext {
	public:
		IOContext();

		shared_ptr<io_context> Get();

	private:
		shared_ptr<io_context> mIOContext {};
	};
}
