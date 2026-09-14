#include "helper.h"
#include "type.h"
#include "pieces.h"
#include "macros.h"
#include "constants.h"


void addMove(moveList *move, int newMove)
{
    move->move[move->count++] = newMove; 
}

static U64 getAttackLookup(int piece, U64 block, int square)
{
    if( piece == N || piece == n){
        return attackLookup.knight[square];
    }
    else if( piece == R || piece == r){
        return getRookAttacks(square, block);
    }
    else if( piece == B || piece == b){
        return getBishopAttacks(square, block);
    }
    else if( piece == Q || piece == q){
        return getQueenAttacks(square, block);
    }
}


// Pseudo-Legal moves ---- checkLegalMove will be made later
void generateMoves(const gameState *state, moveList *move)
{
    generatePawnMoves(state, move);
    generateKingMoves(state, move);
    

    int piece = (state->side == WHITE) ? N : n;
    int end = (state->side == WHITE) ? Q : q;

    for(; piece <= end; piece++)
    {
        U64 board = state->board[piece];

        while(board)
        {
            
            int lsb = get_LSB_index(board);

            U64 attack = getAttackLookup(piece, state->occupancy[BOTH], lsb);

            while(attack){
                int attack_lsb = get_LSB_index(attack);

                if(get(state->occupancy[!state->side], attack_lsb))
                {
                    addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 1, 0, 0, 0));
                } 
                else if(get(~state->occupancy[BOTH], attack_lsb))
                {
                    addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 0, 0, 0, 0));
                }

                remove(attack, attack_lsb);
            }

            remove(board, lsb);
        }
    }

}