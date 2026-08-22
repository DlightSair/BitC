#include "macros.h"
#include "header.h"

void init_reaper_moves(attackTables *attack)
{
    for(int piece=0; piece < SIZE; piece++)
    {
        attack->pawn[WHITE][piece] = maskPawnAttacks(WHITE, piece);
        attack->pawn[BLACK][piece] = maskPawnAttacks(BLACK, piece);

        attack->knight[piece] = maskKnightAttacks(piece);
        attack->king[piece] = maskKingAttacks(piece);
    }

}


