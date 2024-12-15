#include "Tests/pch.h"

#include "Networking/Message/MessageTests.h"
#include "Tests/Networking/TCP/TCPTests.h"

using namespace Networking;
using namespace Message;
using namespace TCP;

// TODO: for testing the server (delete later)
#include "Go/json.hpp"
//
#include "Go/Game/Board.cpp"
#include "Go/Game/Context.cpp"
#include "Go/Game/Player.cpp"
#include "Go/Game/Rules.cpp"
#include "Go/Game/Stone.cpp"
#include "Go/Server/Match.cpp"
#include "Go/Server/MatchManager.cpp"
#include "Go/Server/Server.cpp"

int main()
{
    /*TEST_CLASS(MessageTests);
    TEST_CLASS(TCPTests);*/

    try
    {
        TRACE("Loading rules and creating server...");

        Networking::IOContext context;

        Game::Rules rules;
        if (!rules.LoadFromFile("rules.cfg"))
        {
            TRACE("Config file doesn't exist!");
            return 0;
        }

        ::Server::Server server(context, SERVER_PORT, rules);
        TRACE(format("Server is running with rules({}, {{ {}, {} }}) on {}:{}...", (int)rules.GetPlayersPerMatch(),
                     (int)rules.GetSize().GetXY().first, (int)rules.GetSize().GetXY().second, SERVER_IP, SERVER_PORT)
                  .c_str());

        context.Run();
    }
    catch (const std::exception &aException)
    {
        TRACE(std::format("Exception: {}", aException.what()));
    }

    return 0;
}
