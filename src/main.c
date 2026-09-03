#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"


// GLOBAL VARIBLE ATTACK LOOKUP 
attackTables attackLookup;
attackMasks maskAttacks;

int main()
{
    init_attack_lookup();

    gameState state = {
        .board = {
            0x00FF000000000000ULL,
            0x4200000000000000ULL,
            0x2400000000000000ULL,
            0x8100000000000000ULL,
            0x0800000000000000ULL,
            0x1000000000000000ULL,
            0x000000000000FF00ULL,
            0x0000000000000042ULL,
            0x0000000000000024ULL,
            0x0000000000000081ULL,
            0x0000000000000008ULL,
            0x0000000000000010ULL
        },
        .castle = WK+WQ+BK+BK,
        .enpassant = NO_SQUARE,
        .side = WHITE
    };
 

    printBoard(state.board);
    
    return 0;
}