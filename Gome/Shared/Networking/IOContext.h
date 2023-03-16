#pragma once

namespace Shared::Networking {
	class IOContext {
	public:
		IOContext();

		tcp::socket CreateSocket();
		tcp::resolver CreateResolver();
		tcp::acceptor CreateAcceptor();

		void Run();

		io_context& operator*();

	private:
		shared_ptr<io_context> mIOContext {};
	};
}
