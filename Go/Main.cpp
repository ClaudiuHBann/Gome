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

/*
    TODO:
            - cati clienti s-au conenctat pentru server

            - add comments for the Go project
            - documentatie despre arhitectura si cum functioneaza
*/
