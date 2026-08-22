#include "macros.h"
#include "header.h"

void init_reaper_moves(attackTables *attack)
{
    for(int piece=0; piece < SIZE; piece++)
    {
        attack->pawn[WHITE][piece] = getPawnAttack(WHITE, piece);
        attack->pawn[BLACK][piece] = getPawnAttack(BLACK, piece);

        attack->knight[piece] = getKnightAttack(piece);
    }

}