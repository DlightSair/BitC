#include "helper.h"
#include "pieces.h"
#include "init.h"

static void init_reaper_moves(void)
{
    for(int piece=0; piece < 64; piece++)
    {
        attackLookup.pawn[WHITE][piece] = maskPawnAttacks(WHITE, piece);
        attackLookup.pawn[BLACK][piece] = maskPawnAttacks(BLACK, piece);

        attackLookup.knight[piece] = maskKnightAttacks(piece);
        attackLookup.king[piece] = maskKingAttacks(piece);
    }

}

static void init_masks(void)
{
    for(int i=0; i < 64; i++)
    {
        maskAttacks.rook[i] = maskRookAttacks(i);
        maskAttacks.bishop[i] = maskBishopAttacks(i);
    }
}


static void init_slider_move(void)
{
    for(int square=0; square < 64; square++)
    {
        int occupancy_size_rook = 1 << rook_relevent_bit[square];
        int occupancy_size_bishop = 1 << bishop_relevent_bit[square];

        for(int i=0; i < occupancy_size_rook; i++)
        {
            U64 block = set_occupancy(i, maskAttacks.rook[square]);

            int magicIndex = (int) ( (rook_magicNumbers[square] * block) >> (64 - rook_relevent_bit[square]));
            attackLookup.rook[square][magicIndex] = calculateRookAttacks(square, block);
        }

        for(int i=0; i < occupancy_size_bishop; i++)
        {
            U64 block = set_occupancy(i, maskAttacks.bishop[square]);

            int magicIndex = (int) ( (bishop_magicNumbers[square] * block) >> (64 - bishop_relevent_bit[square]));
            attackLookup.bishop[square][magicIndex] = calculateBishopAttacks(square, block);
        }

    }
}



void init_attack_lookup(void)
{
    init_masks();
    init_reaper_moves();
    init_slider_move();
}


