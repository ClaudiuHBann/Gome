#pragma once

#include "TCPClientRaw.h"

namespace Shared::Networking::Client {
	class TCPClient {
	public:
		using bytes = vector<byte>;

		using CallbackConnect = function<void(error_code, tcp::endpoint)>;
		using CallbackSend = function<void(error_code, size_t)>;
		using CallbackRead = function<void(error_code, String)>;
		using CallbackDisconnect = function<void(error_code, error_code)>;

		TCPClient(IOContext context);

		void Connect(const String& ip, const port_type port, const CallbackConnect& callback);
		void Disconnect(const CallbackDisconnect& callback = [] (auto, auto) {});

		void Send(const String& data, const CallbackSend& callback);
		void Receive(const CallbackRead& callback);

	private:
		IOContext mContext;
		shared_ptr<TCPClientRaw> mTCPClientRaw;
	};
}
