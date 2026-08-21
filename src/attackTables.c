#include "macros.h"


U64 getPawnAttack(int side, int board)
{
    U64 attack = 0ULL;

    switch (side)
    {
    case WHITE:
        attack |= (board >> BOARD_SIZE-1) && notA;
        attack |= (board >> BOARD_SIZE+1) && notH;
        break;

    case BLACK:
        attack |= (board << BOARD_SIZE-1) && notH;
        attack |= (board << BOARD_SIZE+1) && notA;
        break;
    
    default:
        break;
    }

    return attack;
}


