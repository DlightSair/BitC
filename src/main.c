#include "macros.h"
#include "header.h"

int main()
{
    attackTables *attack;

    init_reaper_moves(attack);

    printBitBoard(attack->knight[h1]);


    return 0;
}