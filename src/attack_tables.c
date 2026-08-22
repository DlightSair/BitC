#include "macros.h"
#include "header.h"

U64 getPawnAttack(int side, int piece)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << piece;

    switch (side)
    {
    case WHITE:
        attack |= (board >> BOARD_SIZE-1) & notA;
        attack |= (board >> BOARD_SIZE+1) & notH;
        break;

    case BLACK:
        attack |= (board << BOARD_SIZE-1) & notH;
        attack |= (board << BOARD_SIZE+1) & notA;
        break;
    
    default:
        break;
    }

    return attack;
}

U64 getKnightAttack(int piece)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << piece;

    attack |= (board >> 2*BOARD_SIZE+1) & notH;
    attack |= (board >> 2*BOARD_SIZE-1) & notA;

    attack |= (board << 2*BOARD_SIZE+1) & notA;
    attack |= (board << 2*BOARD_SIZE-1) & notH;


    attack |= (board >> BOARD_SIZE+2) & notGH;
    attack |= (board >> BOARD_SIZE-2) & notAB;

    attack |= (board << BOARD_SIZE+2) & notAB;
    attack |= (board << BOARD_SIZE-2) & notGH;

    return attack;
}


