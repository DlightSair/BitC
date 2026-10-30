#include "helper.h"
#include "type.h"
#include "pieces.h"
#include "macros.h"
#include "constants.h"
#include "zobrist.h"
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

    U64 hash = state->hash;
    hash ^= castleKeys[state->castle];
    hash ^= enpassantKeys[state->enpassant];

    clear_bit(state->board[getPiece(move)], source);
    set_bit(state->board[getPiece(move)], target);

    hash ^= pieceKeys[getPiece(move)][source];
    hash ^= pieceKeys[getPiece(move)][target];

    if(getCapture(move)){
        // clear_bit from opposite board
        int start_piece = (state->side == WHITE) ? p : P; 
        int end_piece = (state->side == WHITE) ? k : K;

        for(int piece = start_piece; piece <= end_piece; piece++)
        {
            if(get_bit(state->board[piece], target)){
                clear_bit(state->board[piece], target);
                hash ^= pieceKeys[piece][target];
                break;
            }
        }
    }


    if(getProm(move)){
        int promotedPiece = getProm(move) - (state->side == WHITE ? 6 : 0);

        clear_bit(state->board[getPiece(move)], target);
        set_bit(state->board[promotedPiece], target);

        hash ^= pieceKeys[getPiece(move)][target];
        hash ^= pieceKeys[promotedPiece][target];
    }


    if(getEnpassant(move)){
        if(state->side == WHITE){
            clear_bit(state->board[ p ], target + 8);
            hash ^= pieceKeys[p][target + 8];
        }
        else{
            clear_bit(state->board[ P ], target - 8);
            hash ^= pieceKeys[P][target - 8];
        }

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
                clear_bit(state->board[rook], h1);
                set_bit(state->board[rook], f1);
                hash ^= pieceKeys[rook][h1] ^ pieceKeys[rook][f1];
                break;

            case c1:
                clear_bit(state->board[rook], a1);
                set_bit(state->board[rook], d1);
                hash ^= pieceKeys[rook][a1] ^ pieceKeys[rook][d1];
                break;

            case g8:
                clear_bit(state->board[rook], h8);
                set_bit(state->board[rook], f8);
                hash ^= pieceKeys[rook][h8] ^ pieceKeys[rook][f8];
                break;

            case c8:
                clear_bit(state->board[rook], a8);
                set_bit(state->board[rook], d8);
                hash ^= pieceKeys[rook][a8] ^ pieceKeys[rook][d8];
                break;

            default:
                break;
        }


    }

    // UPDATE CASTLING RIGHTS 

    // ROOK OR KING MOVED
    switch(source)
    {
    case e1:
        state->castle &= 12; // 1100 : 12
        break;

    case e8:
        state->castle &= 3; // 0011 : 3
        break;

    case h1:
        state->castle &= 14; // 1110 : 14
        break;

    case a1:
        state->castle &= 13; // 1101 : 13
        break;

    case h8:
        state->castle &= 11; // 1011 : 11
        break;

    case a8:
        state->castle &= 7;  // 0111 : 7
        break;

    default:
        break;
    }

    // ROOK CAPTURED
    switch (target)
    {
    case h1:
        state->castle &= 14; // 1110 : 14
        break;

    case a1:
        state->castle &= 13; // 1101 : 13
        break;

    case h8:
        state->castle &= 11; // 1011 : 11
        break;

    case a8:
        state->castle &= 7;  // 0111 : 7
        break;
    }

    
    // Reevaluate occupancy
    memset(state->occupancy, 0, sizeof(state->occupancy));

    for(int piece = P; piece <= K; piece++){
        state->occupancy[WHITE] |= state->board[piece];
    }

   for(int piece = p; piece <= k; piece++){
        state->occupancy[BLACK] |= state->board[piece];
    }

    state->occupancy[BOTH] = state->occupancy[WHITE] | state->occupancy[BLACK];

    // CHECK FOR CHECK
    int king = (state->side == WHITE) ? K : k;
    if( isSquareAttacked(state, get_LSB_index(state->board[king]), !state->side)){
        *state = temp;
        return 0;
    }

    // Fifty move counter resets on pawn moves and captures
    if(getPiece(move) == P || getPiece(move) == p || getCapture(move)){
        state->half = 0;
    }
    else{
        state->half++;
    }

    if(state->side == BLACK) state->full++;

    hash ^= castleKeys[state->castle];
    hash ^= enpassantKeys[state->enpassant];
    hash ^= sideKey;
    state->hash = hash;

    // Change Side
    state->side ^= 1;

    return 1;
}


// Pseudo-Legal moves 
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

                if(get_bit(state->occupancy[!state->side], attack_lsb))
                {
                    addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 1, 0, 0, 0));
                } 
                else if(get_bit(~state->occupancy[BOTH], attack_lsb))
                {
                    addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 0, 0, 0, 0));
                }

                clear_bit(attack, attack_lsb);
            }

            clear_bit(board, lsb);
        }
    }

}