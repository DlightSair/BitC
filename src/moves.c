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
void generateMoves(const gameState *state)
{
    generatePawnMoves(state);
    generateKingMoves(state);
    

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
                    printf("%c Capture - %s:%s\n", asciiPiece[piece], squareToString[lsb], squareToString[attack_lsb]);
                } 
                else if(get(~state->occupancy[BOTH], attack_lsb))
                {
                    printf("%c Move - %s:%s\n", asciiPiece[piece], squareToString[lsb], squareToString[attack_lsb]);
                }

                remove(attack, attack_lsb);
            }

            remove(board, lsb);
        }
    }

}