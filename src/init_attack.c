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


