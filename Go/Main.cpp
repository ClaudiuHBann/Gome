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
            - ContextUninit
            - cati clienti s-au conenctat pentru server
            - mesaj pentru cine trebuie sa mute pentru client
            - dupa o miscare corecta pe la un client sa se tremita la toata lumea state-ul jocului

            - add comments for the Go project
            - documentatie despre arhitectura si cum functioneaza
*/
