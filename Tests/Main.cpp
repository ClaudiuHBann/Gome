#include "Tests/pch.h"

#include "Shared/Networking/Message/MessageTests.h"

#include "Gome/Shared/Networking/IOContext.h"
#include "Gome/Shared/Networking/Server/TCPServerRaw.h"
#include "Gome/Shared/Networking/Client/TCPClient.h"

using namespace Shared;
using namespace Networking;
using namespace Message;
using namespace Server;
using namespace Client;

int main() {
	//TEST_CLASS(MessageTests);

	IOContext context;

	auto server = make_shared<TCPServerRaw>(context, port_type(6969));
	server->Start([](auto client) {
		TRACE(TEXT("Server: A client connected."));
		client->Receive([client](auto, auto tuple) {
			TRACE(TEXT("Server: Received data."));
			client->Send(get<2>(tuple), get<1>(tuple), [](auto, auto) {
				TRACE(TEXT("Server: Sent data."));
				});
			});
		});

	TCPClient client(context.CreateSocket());
	auto&& resolver = context.CreateResolver();
	auto&& endpoints = resolver.resolve(ToStringType<char>(String(TEXT("127.0.0.1"))), ToStringType<char>(ToString(6969)));
	client.Connect(endpoints,
		[&](auto, auto) {
			TRACE(TEXT("Client: Connected."));
			client.Send({ byte('6'), byte('9') }, HeaderMetadata::Type::PING,
				[&](auto, auto) {
					TRACE(TEXT("Client: Sent."));
					client.Receive([](auto, auto tuple) {
						TRACE(TEXT("Client: Received."));
						});
				});
		});

	context.Run();

	return 0;
}

/*
	TODO:
		 - add TCPClient with TCPClientRaw member and use the message manager methods in transferring data
		 - move the callbacks to the end, DON'T COPY THEM
		 - make a class from that message response tuple, or at least an using
		 - a better sending/receiving logic (a sent packet waits a ACK and bis)
		 - I think we cannot stop the Server accepting without our app crashing
		 - should we work just with shared_ptr (like all callbacks and all) because we need something to work with everywhere
		 -
*/