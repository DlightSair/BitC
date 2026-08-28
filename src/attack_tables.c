#include "utils.h"
#include "header.h"

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


// Returns Possible Block Postion Bitboard For Rook
U64 maskRookAttacks(int square)
{
    U64 attack = 0ULL;
    
    int curRank = square / BOARD_SIZE;
    int curFile = square % BOARD_SIZE;

    int r, f;

    for(r = curRank-1, f = curFile; r > 0 ; r--)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));

    for(r = curRank, f = curFile-1; f > 0 ; f--)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));

    for(r = curRank+1, f = curFile; r < BOARD_SIZE-1 ; r++)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
    
   for(r = curRank, f = curFile+1; f < BOARD_SIZE-1 ; f++)
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));


    return attack;
}


// Returns possible Bishop Attacks Bitboard based on Blocker Bitboard
U64 getBishopAttacks(int square, U64 block)
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


// Returns possible Rook Attacks Bitboard based on Blocker Bitboard
U64 getRookAttacks(int square, U64 block)
{
    U64 attack = 0ULL;
    
    int curRank = square / BOARD_SIZE;
    int curFile = square % BOARD_SIZE;

    int r, f;

    for(r = curRank-1, f = curFile; r >= 0 ; r--){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block )
            break;
    }

    for(r = curRank, f = curFile-1; f >= 0 ; f--){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block )
            break;
    }

    for(r = curRank+1, f = curFile; r < BOARD_SIZE ; r++){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block )
            break;
    }
    
   for(r = curRank, f = curFile+1; f < BOARD_SIZE ; f++){
        attack |= ( 1ULL << ( r * BOARD_SIZE + f ));
        if( ( 1ULL << ( r * BOARD_SIZE + f )) & block )
            break;
    }

    return attack;
}

