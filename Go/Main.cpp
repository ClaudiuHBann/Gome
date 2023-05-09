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
            - meciul se termina cand nimeni nu poate sa mai faca vreo miscare
            - castigatorul meciului este cel cu cele mai multe pietre pe tabla, iar daca sunt 2 sau mai multi cu acelasi
   numar de piese pe tabla se va alege ultimul care a facut miscarea dintre ei
*/
