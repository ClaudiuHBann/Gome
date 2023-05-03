#include "pch.h"

#include "Go/Game.h"

int main()
{
    GameI({6, 10}).Run();

    return 0;
}

/*
    TO DO:
    check   - serverul sa astepte intre 2-5 jucatori si sa ii bage in meci, apoi ascultand mai departe
    check   - ficarui jucator din meci i se va da o culoare
            - fiecare jucator trebuie sa puna o piatra pe rand
    check    - tabla de joc e de 6x10
    check   - la inceperea meciului serverul va face o mutare pentru fiecare jucator
            - ordinea jucatorilor este cea a conectarii la server
            - o piatra se poate amplasa doar intr-o celula libera si cu cel putin o piatra vecina de aceeasi culoare
            - fiecare jucator are 3 jokeri care ii poate folosi cand ii e randul si doar odata:
                - Joker Double Move - 2 mutari consecutive
                - Joker Replace - poate plasa o piatra proprie pe o piatra inamica dar trebuie sa aiba o piatra a lui
   vecina
                - Joker Freedom - poate plasa o piatra oriunde intr-o celula libera
        *   - daca un jucator nu poate face nici o mutare inclusiv cu un joker se trece mai departe
        *   - meciul se termina cand nimeni nu poate sa mai faca vreo miscare
        *   - castigatorul meciului este cel cu cele mai multe pietre pe tabla, iar daca sunt 2 sau mai multi cu acelasi
   numar de piese pe tabla se va alege ultimul care a facut miscarea dintre ei
*/
