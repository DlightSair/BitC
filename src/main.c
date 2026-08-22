#include "macros.h"
#include "header.h"

int main()
{
    attackTables *attack;

    init_reaper_moves(attack);

    printBitBoard(maskRookAttacks(a6));


    return 0;
}