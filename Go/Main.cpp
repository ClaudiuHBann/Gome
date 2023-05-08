#include "pch.h"

#include "Go/Client/Game.h"

int main()
{
    Networking::IOContext context;
    Client::GameI(context).Run();

    context.Run();

    return 0;
}

/*
    TODO:
            - Joker Double Move - 2 mutari consecutive
            - daca un jucator nu poate face nici o mutare inclusiv cu un joker se trece mai departe
            - meciul se termina cand nimeni nu poate sa mai faca vreo miscare
            - castigatorul meciului este cel cu cele mai multe pietre pe tabla, iar daca sunt 2 sau mai multi cu acelasi
   numar de piese pe tabla se va alege ultimul care a facut miscarea dintre ei
*/

// TODO: add comments
