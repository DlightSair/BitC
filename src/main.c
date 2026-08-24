#include "utils.h"
#include "header.h"



int main()
{
    init_attack_lookup();

    U64 block = 0ULL;
    add(block, c5); add(block, d7);

    printBitBoard(block);
    printf("%d", get_LSB_index(block));


    return 0;
}