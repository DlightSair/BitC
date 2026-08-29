#include "helper.h"
#include "pieces.h"
#include "random.h"
#include "init.h"

#include <string.h>


// For Rook and Bishop
static U64 get_magic_number(int square, int piece)
{
    int relevent_bits = (piece == ROOK) ? rook_relevent_bit[square] : bishop_relevent_bit[square];
    int occupancy_size = 1 << relevent_bits;

    U64 occupancies[4096]; // MAX OCCUPANCY (for rook 2^12)
    U64 attacks[4096];
    U64 used_attacks[4096];

    U64 attack_mask = (piece == ROOK) ? maskRookAttacks(square) : maskBishopAttacks(square);

    for(int i=0; i < occupancy_size; i++)
    {
        occupancies[i] = set_occupancy(i, attack_mask);
        attacks[i] = (piece == ROOK) ? calculateRookAttacks(square, occupancies[i]) : calculateBishopAttacks(square, occupancies[i]);
    }



    int SEARCH_SIZE = 100000000; 

    for(int i=0; i < SEARCH_SIZE; i++)
    {
        U64 magicNumber = get_magnic_number_candidate();

        if(count_bits((magicNumber * attack_mask) & 0xFF00000000000000) < 6) continue;

        memset(used_attacks, 0ULL, sizeof(used_attacks));

        int fail = 0;

        for(int i=0; !fail && i < occupancy_size; i++)
        {
            int magic_index = (int) ((magicNumber * occupancies[i]) >> (SIZE - relevent_bits));

            if( used_attacks[magic_index] == 0ULL){
                used_attacks[magic_index] = attacks[i];
            } else if( used_attacks[magic_index] != attacks[i] ){
                fail = 1;
            }

        }

        if(!fail) return magicNumber;
        
    }

    printf("Magic Number Not Found!\n");
    return 0ULL;


}


// Generating Magic Numbers for Rook and Bishop
void init_magicNumbers(void)
{
    printf("\nROOK:\n");
    for(int i=0; i < SIZE; i++){
        U64 magicNumber = get_magic_number(i, ROOK);
        printf("0x%016" PRIx64 "ULL,\n", magicNumber);
    }

    printf("\n\nBISHOP:\n");

    for(int i=0; i < SIZE; i++){
        U64 magicNumber = get_magic_number(i, BISHOP);
        printf("0x%016" PRIx64 "ULL,\n", magicNumber);

    }
}

