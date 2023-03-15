#pragma once

#include "Gome/Shared/Utility/String.h"

namespace Shared::Networking::Client {
	using namespace Utility;

	class TCPClientRaw : public enable_shared_from_this<TCPClientRaw> {
	public:
		using bytes = vector<byte>;

		using CallbackConnect = function<void(error_code, tcp::endpoint)>;
		using CallbackWrite = function<void(error_code, size_t)>;
		using CallbackRead = function<void(error_code, size_t)>;

		TCPClientRaw(io_context& context);
		~TCPClientRaw();

		const tcp::socket& GetSocket() const;

		void ConnectAsync(const String& ip, const port_type port, const CallbackConnect& callback);
		pair<error_code, error_code> Disconnect();

		void SendAsync(const shared_ptr<bytes>& data, const CallbackWrite& callback);
		void ReadAsync(const shared_ptr<bytes>& data, const CallbackRead& callback);

	private:
		io_context& mContext;
		tcp::socket mSocket;
	};
}
