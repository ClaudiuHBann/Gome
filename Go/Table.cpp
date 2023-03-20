#include "Go/pch.h"
//
#include "Table.h"
//

Table::Table(const size_t sizeRows, const size_t sizeColumns) : mSizeRows(sizeRows), mSizeColumns(sizeColumns)
{
}

void Table::Draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {});

    for (size_t i = 0; i <= mSizeColumns; i++)
    {
        cout << i << ' ';
    }
    cout << endl;

    cout << ' ' << unsigned char(218);
    for (size_t i = 0; i < mSizeColumns - 1; i++)
    {
        cout << unsigned char(196) << unsigned char(194);
    }
    cout << unsigned char(196) << unsigned char(191) << endl;

    for (size_t i = 1; i < mSizeRows; i++)
    {
        cout << i;
        for (size_t j = 0; j < mSizeColumns; j++)
        {
            cout << unsigned char(179) << ' ';
        }
        cout << unsigned char(179) << endl;

        cout << ' ' << unsigned char(195);
        for (size_t j = 0; j < mSizeColumns - 1; j++)
        {
            cout << unsigned char(196) << unsigned char(197);
        }
        cout << unsigned char(196) << unsigned char(180) << endl;
    }

    cout << mSizeRows;
    for (size_t j = 0; j < mSizeColumns; j++)
    {
        cout << unsigned char(179) << ' ';
    }
    cout << unsigned char(179) << endl;

    cout << ' ' << unsigned char(192);
    for (size_t j = 0; j < mSizeColumns - 1; j++)
    {
        cout << unsigned char(196) << unsigned char(193);
    }
    cout << unsigned char(196) << unsigned char(217) << endl;
}

void Table::DrawStone(const Stone &stone, const Color color)
{
    COORD pos = {(short)stone.GetPosition().first, (short)stone.GetPosition().second};
    pos.X = pos.X * 2 + 2;
    pos.Y = pos.Y * 2 + 2;

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);

    cout << format("\x1B[{}m{}\033[0m\t\t", (size_t)color, char(2));
}
