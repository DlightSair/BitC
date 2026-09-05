#include "helper.h"
#include "pieces.h"
#include "type.h"


int isSquareAttacked(U64 board[], U64 occupancy[], int square, int side)
{
    return 
        (side == WHITE) && (attackLookup.pawn[BLACK][square] & board[P]) ||

        (side == BLACK) && (attackLookup.pawn[WHITE][square] & board[p]) ||

        attackLookup.knight[square] & ((side == WHITE) ? board[N] : board[n]) ||

        attackLookup.king[square] & ((side == WHITE) ? board[K] : board[k]) ||

        getBishopAttacks(square, occupancy[BOTH]) & ((side == WHITE) ? board[B] : board[b]) ||

        getRookAttacks(square, occupancy[BOTH]) & ((side == WHITE) ? board[R] : board[r]) ||

        getQueenAttacks(square, occupancy[BOTH]) & ((side == WHITE) ? board[Q] : board[q]);
}


void printAttackedBoard(gameState state)
{
    U64 attack = 0ULL;

    for(int r = 0; r < BOARD_SIZE; r++)
    {
        for(int f = 0; f < BOARD_SIZE; f++)
        {
            int square = r*BOARD_SIZE + f;
            
            if( isSquareAttacked(state.board, state.occupancy, square, state.side) )
                set(attack, square);

        }
    }

    printBitBoard(attack & ~state.occupancy[state.side]);
}