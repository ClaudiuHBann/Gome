#include "Gome/pch.h"
#include "TCPClientRaw.h"

namespace Shared::Networking::Client {
	TCPClientRaw::TCPClientRaw(io_context& context)
		: mContext(context),
		mSocket(mContext) {
	}

	TCPClientRaw::~TCPClientRaw() {
		Disconnect();
	}

	const tcp::socket& TCPClientRaw::GetSocket() const {
		return mSocket;
	}

	void TCPClientRaw::ConnectAsync(const String& ip, const port_type port, const CallbackConnect& callback) {
		tcp::resolver resolver(mContext);
		auto endpoints = resolver.resolve(ToStringType<char>(ip), ToStringType<char>(ToString(port)));

		auto self(shared_from_this());
		async_connect(mSocket, endpoints,
					  [self, callback] (const auto& ec, const auto& ep) {
						  callback(ec, ep);
					  });
	}

	void TCPClientRaw::SendAsync(const shared_ptr<bytes>& data, const CallbackWrite& callback) {
		auto self(shared_from_this());
		async_write(mSocket, asio::buffer(*data),
					[self, data, callback] (const auto& ec, const auto& size) {
						callback(ec, size);
					});
	}

	void TCPClientRaw::ReadAsync(const shared_ptr<bytes>& data, const CallbackRead& callback) {
		auto self(shared_from_this());
		async_read(mSocket, asio::buffer(*data),
				   [self, data, callback] (const auto& ec, const auto& size) {
					   callback(ec, size);
				   });
	}

	pair<error_code, error_code> TCPClientRaw::Disconnect() {
		error_code ec1, ec2;

		mSocket.shutdown(tcp::socket::shutdown_both, ec1);
		mSocket.close(ec2);

		return { ec1, ec2 };
	}
}
