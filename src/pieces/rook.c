#include "helper.h"
#include "pieces.h"


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






// Returns possible Rook Attacks Bitboard based on Blocker Bitboard
U64 calculateRookAttacks(int square, U64 block)
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



U64 getRookAttacks(int square, U64 block)
{
    block &= maskAttacks.rook[square];
    int magicIndex = (int) ( (rook_magicNumbers[square] * block) >> (SIZE - rook_relevent_bit[square]));

    return attackLookup.rook[square][magicIndex];
}


void generateRookAttacks(U64 RookBoard, U64 occupancy[], int side)
{
    while(RookBoard)
    {
        int lsb = get_LSB_index(RookBoard);

        U64 RookAttack = attackLookup.knight[lsb];

        while(RookAttack){
            int attack_lsb = get_LSB_index(RookAttack);

            if(get(occupancy[!side], attack_lsb))
            {
                printf("Knight Capture %s:%s\n", squareToString[lsb], squareToString[attack_lsb]);
            } 
            else if(get(~occupancy[BOTH], attack_lsb))
            {
                printf("Knight %s:%s\n", squareToString[lsb], squareToString[attack_lsb]);
            }

            remove(RookAttack, attack_lsb);
        }

        remove(RookBoard, lsb);
    }
}