#include "Tests/pch.h"
#include "Shared/Networking/Message/MessageTests.h"
#include "Gome/Shared/Networking/Client/TCPClientRaw.h"

using namespace Shared;
using namespace Networking;
using namespace Message;

int main() {
	//TEST_CLASS(MessageTests);

	io_context context;


	auto tcpClient = make_shared<Client::TCPClientRaw>(context);
	tcpClient->ConnectAsync(TEXT("162.55.32.18"), 32406,
							[&] (auto, auto) {
								TRACE(TEXT("Connected!"));
	auto buffer = make_shared<Client::TCPClientRaw::bytes>(10);
	tcpClient->ReadAsync(buffer,
						 [&, buffer] (auto, auto) {
							 TRACE(TEXT("Received ") << buffer.get()->size() << TEXT(" bytes!"));

	auto data = make_shared<vector<byte>>();
	data->push_back((byte)'6');
	data->push_back((byte)'9');

	tcpClient->SendAsync(data,
						 [] (auto, auto) {
							 TRACE(TEXT("Sent!"));
						 });
						 });
							});

	context.run();

	return 0;
}