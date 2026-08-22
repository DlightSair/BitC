#include "macros.h"
#include "header.h"

U64 maskPawnAttacks(int side, int piece)
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

U64 maskKnightAttacks(int piece)
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


U64 maskKingAttacks(int piece)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << piece;

    attack |= (board << BOARD_SIZE);
    attack |= (board >> BOARD_SIZE);

    attack |= (board << 1) & notA;
    attack |= (board >> 1) & notH;

    attack |= (board << BOARD_SIZE+1) & notA;
    attack |= (board << BOARD_SIZE-1) & notH;

    attack |= (board >> BOARD_SIZE+1) & notH;
    attack |= (board >> BOARD_SIZE-1) & notA;

    return attack;
}


U64 maskBishopAttacks(int piece)
{
    U64 attack = 0ULL;
    
    int curRank = piece / BOARD_SIZE;
    int curFile = piece % BOARD_SIZE;

    int r, f;

    for(r = curRank+1, f = curFile+1; r < BOARD_SIZE-1 && f < BOARD_SIZE-1; r++, f++)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));

    for(r = curRank-1, f = curFile+1; r > 0 && f < BOARD_SIZE-1; r--, f++)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));

    for(r = curRank-1, f = curFile-1; r > 0 && f > 0; r--, f--)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));

    for(r = curRank+1, f = curFile-1; r < BOARD_SIZE-1 && f > 0; r++, f--)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));


    return attack;
}


