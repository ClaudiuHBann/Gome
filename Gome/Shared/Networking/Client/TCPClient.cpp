#include "Gome/pch.h"
#include "TCPClient.h"
#include "Gome/Shared/Networking/Message/MessageManager.h"
#include "Gome/Shared/Networking/Message/MessageConverter.h"

namespace Shared::Networking::Client {
	using namespace Message;

	TCPClient::TCPClient(IOContext context)
		: mContext(context),
		mTCPClientRaw(make_shared<TCPClientRaw>(context)) {
	}

	void TCPClient::Connect(const String& ip, const port_type port, const CallbackConnect& callback) {
		mTCPClientRaw->ConnectAsync(ip, port, callback);
	}

	void TCPClient::Disconnect(const CallbackDisconnect& callback /* = [] (auto, auto) {} */) {
		mTCPClientRaw->Disconnect(callback);
	}

	void TCPClient::Send(const String& data, const CallbackSend& callback) {
		auto dataSizeInBytes = data.length() * sizeof(String::value_type);
		auto dataAsBytesRaw = (bytes*)data.data();
		bytes dataAsBytes(dataAsBytesRaw->begin(), dataAsBytesRaw->begin() + dataSizeInBytes);

		MessageManager manager;
		auto message = manager.ToMessage(dataAsBytes, HeaderMetadata::Type::TEXT);

		auto bytes = MessageConverter::MessageToBytes(message);
		auto bytesShared = make_shared<decltype(bytes)>(bytes);

		mTCPClientRaw->SendAllAsync(bytesShared,
									[callback] (auto ec, auto size) {
										callback(ec, size);
									});
	}

	void TCPClient::Receive(const CallbackRead& callback) {
		auto data = make_shared<bytes>();

		// TODO: WRONGHIX
		mTCPClientRaw->ReceiveAllAsync(data,
									   [callback] (auto ec, auto size) {
										   callback(ec, size);
									   });
	}
}
