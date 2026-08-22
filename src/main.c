#include "utils.h"
#include "header.h"

// GLOBAL VARIBLE ATTACK FOR ATTACK LOOKUP
attackTables attackLookup;



int main()
{
    init_reaper_moves();

    U64 block = 0ULL;
    add(block, c5); add(block, d7);

    printBitBoard(block);
    printf("%d", count_bits(block));


    return 0;
}