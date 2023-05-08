#include "Tests/pch.h"

#include "Networking/Message/MessageTests.h"
#include "Tests/Networking/TCP/TCPTests.h"

using namespace Networking;
using namespace Message;
using namespace TCP;

// for testing the server (TODO: delete)
#include "Go/json.hpp"
//
#include "Go/Game/Board.cpp"
#include "Go/Game/Player.cpp"
#include "Go/Game/Stone.cpp"
#include "Go/Server/Match.cpp"
#include "Go/Server/Server.cpp"

int main()
{
    TEST_CLASS(MessageTests);
    TEST_CLASS(TCPTests);

    Networking::IOContext context;

    Game::Rules rules(2, {6, 10});
    ::Server::Server server(context, SERVER_PORT, rules);

    context.Run();

    return 0;
}
