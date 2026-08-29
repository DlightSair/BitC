#include "helper.h"
#include "pieces.h"


// Returns Possible Knight Attack Bitboard
U64 maskKnightAttacks(int square)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << square;

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