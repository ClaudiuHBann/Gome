#include "Gome/pch.h"
#include "TCPClientRaw.h"

namespace Shared::Networking::Client {
	TCPClientRaw::TCPClientRaw(tcp::socket&& socket)
	  : mSocket(make_unique<tcp::socket>(move(socket))) {
	}

	TCPClientRaw::~TCPClientRaw() {
		Disconnect();
	}

	const unique_ptr<tcp::socket>& TCPClientRaw::GetSocket() const {
		return mSocket;
	}

	void TCPClientRaw::ConnectAsync(const basic_resolver_results<tcp>& endpoints, const CallbackConnect& callback) {
		auto self(shared_from_this());
		// TODO endpoints still exists?
		async_connect(*mSocket, endpoints,
					  [self, callback] (const auto& ec, const auto& ep) {
						  callback(ec, ep);
					  });
	}

	void TCPClientRaw::SendAsync(const shared_ptr<bytes>& data, const CallbackSend& callback) {
		auto self(shared_from_this());
		async_write(*mSocket, asio::buffer(*data),
					[self, data, callback] (const auto& ec, const auto& size) {
						callback(ec, size);
					});
	}

	void TCPClientRaw::SendAllAsync(const shared_ptr<bytes>& data, const CallbackSend& callback) {
		auto self(shared_from_this());
		async_write(*mSocket, asio::buffer(*data),
					[&, self, data, callback] (const auto& ec, const auto& size) {
						if (ec) {
							callback(ec, size);
						} else {
							SendShardAsync(data, size, callback);
						}
					});
	}

	void TCPClientRaw::SendShardAsync(const shared_ptr<bytes>& data, const size_t offset, const CallbackSend& callback) {
		auto self(shared_from_this());
		async_write(*mSocket, asio::buffer(data->data() + offset, data->size() - offset),
					[&, self, data, callback, offset] (const auto& ec, const auto& size) {
						if (ec) {
							callback(ec, offset + size);
						} else {
							SendShardAsync(data, offset + size, callback);
						}
					});
	}

	void TCPClientRaw::ReceiveAsync(const shared_ptr<bytes>& data, const CallbackRead& callback) {
		auto self(shared_from_this());
		async_read(*mSocket, asio::buffer(*data),
				   [self, data, callback] (const auto& ec, const auto& size) {
					   data->resize(size);
		callback(ec, data);
				   });
	}

	void TCPClientRaw::ReceiveAllAsync(const shared_ptr<bytes>& data, const CallbackRead& callback) {
		auto self(shared_from_this());
		async_read(*mSocket, asio::buffer(*data),
				   [&, self, data, callback] (const auto& ec, const auto& size) {
					   if (ec) {
						   data->resize(size);
						   callback(ec, data);
					   } else {
						   ReceiveShardAsync(data, size, callback);
					   }
				   });
	}

	void TCPClientRaw::ReceiveShardAsync(const shared_ptr<bytes>& data, const size_t offset, const CallbackRead& callback) {
		auto self(shared_from_this());
		async_read(*mSocket, asio::buffer(data->data() + offset, data->size() - offset),
				   [&, self, data, callback, offset] (const auto& ec, const auto& size) {
					   if (ec) {
						   data->resize(offset + size);
						   callback(ec, data);
					   } else {
						   ReceiveShardAsync(data, offset + size, callback);
					   }
				   });
	}

	void TCPClientRaw::Disconnect(const CallbackDisconnect& callback /* = [] (auto, auto) {} */) {
		error_code ec1, ec2;

		mSocket->shutdown(tcp::socket::shutdown_both, ec1);
		mSocket->close(ec2);

		callback(ec1, ec2);
	}
}
