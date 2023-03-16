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

	return 0;
}

/*
	TODO:
		 - add TCPClient with TCPClientRaw member and use the message manager methods in transferring data
		 - move the callbacks to the end, DON'T COPY THEM
		 - make a class from that message response tuple, or at least an using
		 - a better sending/receiving logic (a sent packet waits a ACK and bis)
		 -
*/