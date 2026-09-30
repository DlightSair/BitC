#include "helper.h"
#include "pieces.h"
#include "type.h"

// is square <square> attacked by side <side>
int isSquareAttacked(const gameState *s, int square, int side)
{
    return 
        (side == WHITE) && (attackLookup.pawn[BLACK][square] & s->board[P]) ||

        (side == BLACK) && (attackLookup.pawn[WHITE][square] & s->board[p]) ||

        attackLookup.knight[square] & ((side == WHITE) ? s->board[N] : s->board[n]) ||

        attackLookup.king[square] & ((side == WHITE) ? s->board[K] : s->board[k]) ||

        getBishopAttacks(square, s->occupancy[BOTH]) & ((side == WHITE) ? s->board[B] : s->board[b]) ||

        getRookAttacks(square, s->occupancy[BOTH]) & ((side == WHITE) ? s->board[R] : s->board[r]) ||

        getQueenAttacks(square, s->occupancy[BOTH]) & ((side == WHITE) ? s->board[Q] : s->board[q]);
}


void printAttackedBoard(const gameState *state)
{
    U64 attack = 0ULL;

    for(int r = 0; r < BOARD_SIZE; r++)
    {
        for(int f = 0; f < BOARD_SIZE; f++)
        {
            int square = r*BOARD_SIZE + f;
            
            if( isSquareAttacked(state, square, !state->side) )
                set(attack, square);

        }
    }

    printBitBoard(attack & ~state->occupancy[state->side]);
}