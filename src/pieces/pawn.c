#include "helper.h"
#include "pieces.h"

// Returns Possible Pawn Attack Bitboard
U64 maskPawnAttacks(int side, int square)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << square;

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