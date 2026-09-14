#include "helper.h"
#include "pieces.h"


// Returns Possible King Attack Bitboard
U64 maskKingAttacks(int square)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << square;

    attack |= (board << BOARD_SIZE);
    attack |= (board >> BOARD_SIZE);

    attack |= (board << 1) & notA;
    attack |= (board >> 1) & notH;

    attack |= (board << BOARD_SIZE+1) & notA;
    attack |= (board << BOARD_SIZE-1) & notH;

    attack |= (board >> BOARD_SIZE+1) & notH;
    attack |= (board >> BOARD_SIZE-1) & notA;

    return attack;
}


 

void generateKingMoves(const gameState *state, moveList *move)
{
    U64 empty = ~state->occupancy[BOTH];
    U64 kingBoard = (state->side == WHITE) ? state->board[K] : state->board[k];
    int piece = (state->side == WHITE) ? K : k;
    int ksCastleColor = (state->side == WHITE) ? WK : BK;
    int qsCastleColor = (state->side == WHITE) ? WQ : BQ;
    int kOffset = (state->side == WHITE) ? 0 : -7*8;

    
    if( state->castle & ksCastleColor){
        if(!isSquareAttacked(state, f1 + kOffset, !state->side) 
            && !isSquareAttacked(state, g1 + kOffset, !state->side))
        {
            if(get(empty, f1 + kOffset) && get(empty, g1 + kOffset))
            {
                addMove(move, encodeMove(e1+kOffset, g1+kOffset, piece, 0, 0, 0, 0, 1));
            }
        }
    }

    if( state->castle & qsCastleColor){
        if(!isSquareAttacked(state, b1 + kOffset, !state->side) 
            && !isSquareAttacked(state, c1 + kOffset, !state->side) 
            && !isSquareAttacked(state, d1 + kOffset, !state->side))
        {
            
            if(get(empty, b1 + kOffset) && get(empty, c1 + kOffset) && get(empty, d1 + kOffset))
            {
                addMove(move, encodeMove(e1+kOffset, b1+kOffset, piece, 0, 0, 0, 0, 1));
            }
        }
    }

    
    // only one king but still eh 
    while(kingBoard)
    {
        int lsb = get_LSB_index(kingBoard);

        U64 kingAttack = attackLookup.king[lsb];

        while(kingAttack){
            int attack_lsb = get_LSB_index(kingAttack);

            if(get(state->occupancy[!state->side], attack_lsb))
            {
                addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 1, 0, 0, 0));
            } 
            else if(get(empty, attack_lsb))
            {
                addMove(move, encodeMove(lsb, attack_lsb, piece, 0, 0, 0, 0, 0));
            }

            remove(kingAttack, attack_lsb);
        }

        remove(kingBoard, lsb);
    }
}