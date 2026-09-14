#include "helper.h"
#include "pieces.h"

// Returns Possible Block Postion Bitboard for Bishop
U64 maskBishopAttacks(int square)
{
    U64 attack = 0ULL;
    
    int curRank = square / BOARD_SIZE;
    int curFile = square % BOARD_SIZE;

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



// Returns possible Bishop Attacks Bitboard based on Blocker Bitboard
U64 calculateBishopAttacks(int square, U64 block)
{
    U64 attack = 0ULL;
    
    int curRank = square / BOARD_SIZE;
    int curFile = square % BOARD_SIZE;

    int r, f;

    for(r = curRank+1, f = curFile+1; r < BOARD_SIZE && f < BOARD_SIZE; r++, f++){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block)
            break;
    }

    for(r = curRank-1, f = curFile+1; r >= 0 && f < BOARD_SIZE; r--, f++){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block)
            break;
    }

    for(r = curRank-1, f = curFile-1; r >= 0 && f >= 0; r--, f--){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block)
            break;
    }

    for(r = curRank+1, f = curFile-1; r < BOARD_SIZE && f >= 0; r++, f--){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block)
            break;
    }

    return attack;
}



U64 getBishopAttacks(int square, U64 block)
{
    block &= maskAttacks.bishop[square];
    int magicIndex = (int) ( (bishop_magicNumbers[square] * block) >> (SIZE - bishop_relevent_bit[square]));

    return attackLookup.bishop[square][magicIndex];
}

