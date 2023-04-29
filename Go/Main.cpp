#include "pch.h"

#include "Go/Game/Board.h"

using namespace Game;

int main()
{
    SetConsoleOutputCP(437);

    Board board(6, 10);

    while (true)
    {
        board.Draw();
        cin.get();
    }

    return 0;
}
