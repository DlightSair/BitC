#include "macros.h"
#include "header.h"

int main()
{
    attackTables *attack;

    init_reaper_moves(attack);

    printBitBoard(maskBishopAttacks(d4));


    return 0;
}