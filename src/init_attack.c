#include "utils.h"
#include "header.h"

void init_reaper_moves()
{
    for(int piece=0; piece < SIZE; piece++)
    {
        attackLookup.pawn[WHITE][piece] = maskPawnAttacks(WHITE, piece);
        attackLookup.pawn[BLACK][piece] = maskPawnAttacks(BLACK, piece);

        attackLookup.knight[piece] = maskKnightAttacks(piece);
        attackLookup.king[piece] = maskKingAttacks(piece);
    }

}

void init_masks()
{
    for(int i=0; i < SIZE; i++)
    {
        maskAttacks.rook[i] = maskRookAttacks(i);
        maskAttacks.bishop[i] = maskBishopAttacks(i);
    }
}


void init_slider_move()
{
    for(int square=0; square < SIZE; square++)
    {
        int occupancy_size_rook = 1 << rook_relevent_bit[square];
        int occupancy_size_bishop = 1 << bishop_relevent_bit[square];

        for(int i=0; i < occupancy_size_rook; i++)
        {
            U64 block = set_occupancy(i, maskAttacks.rook[square]);

            int magicIndex = (int) ( (rook_magicNumbers[square] * block) >> (SIZE - rook_relevent_bit[square]));
            attackLookup.rook[square][magicIndex] = calculateRookAttacks(square, block);
        }

        for(int i=0; i < occupancy_size_bishop; i++)
        {
            U64 block = set_occupancy(i, maskAttacks.bishop[square]);

            int magicIndex = (int) ( (bishop_magicNumbers[square] * block) >> (SIZE - bishop_relevent_bit[square]));
            attackLookup.bishop[square][magicIndex] = calculateBishopAttacks(square, block);
        }

    }
}




void init_attack_lookup()
{
    init_masks();
    init_reaper_moves();
    init_slider_move();
}


