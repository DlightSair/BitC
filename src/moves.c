#include "helper.h"
#include "type.h"
#include "pieces.h"
#include "macros.h"
#include "constants.h"
#include <string.h>


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


int makeMove(gameState *state, int move)
{
    gameState temp = *state;

    int target = getTarget(move);
    int source = getSource(move);

    remove(state->board[getPiece(move)], source);
    set(state->board[getPiece(move)], target);

    if(getCapture(move)){
        // Remove from opposite board
        int start_piece = (state->side == WHITE) ? p : P; 
        int end_piece = (state->side == WHITE) ? k : K;

        for(int piece = start_piece; piece <= end_piece; piece++)
        {
            if(get(state->board[piece], target)){
                remove(state->board[piece], target);
                break;
            }
        }
    }


    if(getProm(move)){
        remove(state->board[getPiece(move)], target);
        set(state->board[ getProm(move) ], target);
    }


    if(getEnpassant(move)){
        (state->side == WHITE) ? remove(state->board[ p ], target + 8) :
                                 remove(state->board[ P ], target - 8) ;
        
    }

    state->enpassant = NO_SQUARE;


    if(getDouble(move)){
        state->enpassant = target + ((state->side == WHITE) ? +8 : -8); 
    }


    if(getCastle(move)){
        int rook = (state->side == WHITE) ? R : r;
        switch(target)
        {
            case g1:
                remove(state->board[rook], h1);
                set(state->board[rook], f1);
                break;

            case c1:
                remove(state->board[rook], a1);
                set(state->board[rook], d1);
                break;

            case g8:
                remove(state->board[rook], h8);
                set(state->board[rook], f8);
                break;

            case c8:
                remove(state->board[rook], a8);
                set(state->board[rook], d8);
                break;

            default:
                break;
        }


    }

    // UPDATE CASTLING RIGHTS
    switch(source)
    {
    case e1:
        state->castle &= 1100;
        break;

    case e8:
        state->castle &= 0011;
        break;

    case h1:
        state->castle &= 1110;
        break;

    case a1:
        state->castle &= 1101;
        break;

    case h8:
        state->castle &= 1011;
        break;

    case a8:
        state->castle &= 0111; 
        break;

    default:
        break;
    }

    // CHECK FOR CHECK
    int king = (state->side == WHITE) ? K : k;
    if( isSquareAttacked(state, get_LSB_index(state->board[king]), !state->side)){
        *state = temp;
        return 0;
    }

    // Reevaluate occupancy
    memset(state->occupancy, 0, sizeof(state->occupancy));

    for(int piece = P; piece < K; piece++){
        state->occupancy[WHITE] |= state->board[piece];
    }

   for(int piece = p; piece < k; piece++){
        state->occupancy[BLACK] |= state->board[piece];
    }

    state->occupancy[BOTH] = state->occupancy[WHITE] | state->occupancy[BLACK];

    // Change Side
    state->side ^= 1;

    return 1;
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