#include "helper.h"
#include "pieces.h"


// Returns Possible King Attack Bitboard
U64 maskKingAttacks(int square)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << square;

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




void generateKingMoves()
{

}