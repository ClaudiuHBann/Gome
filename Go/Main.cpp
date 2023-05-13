#include "pch.h"

#include "Go/Client/Game.h"

int main()
{
    Networking::IOContext context;
    Client::GameI game(context);
    std::thread([&]() { game.Run(); }).detach();

    context.Run();

    return 0;
}

// color the color in with the color
// cancel joker
// joker used color with red and the ready with green
// when you are the player to move say "you are next"
