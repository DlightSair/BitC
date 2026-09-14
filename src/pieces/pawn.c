#include "helper.h"
#include "pieces.h"
#include "constants.h"

// Returns Possible Pawn Attack Bitboard
U64 maskPawnAttacks(int side, int square)
{
    U64 attack = 0ULL;
    U64 board = 1ULL << square;

    switch (side)
    {
    case WHITE:
        attack |= (board >> BOARD_SIZE-1) & notA;
        attack |= (board >> BOARD_SIZE+1) & notH;
        break;

    case BLACK:
        attack |= (board << BOARD_SIZE-1) & notH;
        attack |= (board << BOARD_SIZE+1) & notA;
        break;
    
    default:
        break;
    }

    return attack;
}



static U64 shiftBitbaord(U64 board, int n)
{
    if(n > 0) return board >> n;
    else return board << -n;
}


void generatePawnMoves(const gameState *state, moveList *move)
{

//    U64 singlePush = shiftBitbaord(pawnBoard, 8 - 16*side) 
//        & (~occupancy);
//
//    U64 doublePush = shiftBitbaord(singlePush, 8 - 16*side) 
//        & (~occupancy) 
//        & (0x00000000FF000000ULL << (8 * side));
    int side = state->side;
    int piece = (side == WHITE) ? P : p;
    U64 pawnBoard = state->board[piece];
    int enpassant = state->enpassant;

    U64 empty = ~state->occupancy[BOTH];
    U64 rank_w2_b7 = (side == WHITE) ? 0x00FF000000000000ULL : 0x000000000000FF00ULL;
    U64 rank_w8_b1 = (side == WHITE) ? 0x00000000000000FFULL : 0xFF00000000000000ULL;
    int shift_offset = (side == WHITE) ? -8 : 8;

    while(pawnBoard)
    {
        int pieceSquare = get_LSB_index(pawnBoard);
        int firstPushSquare = pieceSquare + shift_offset;
        int secondPushSquare = firstPushSquare + shift_offset; 

        
        int isSinglePushValid = get(empty, firstPushSquare);
        int isDoublePushValid = isSinglePushValid 
                            && get(empty, secondPushSquare)
                            && get(rank_w2_b7, pieceSquare);

        // Pawn Promotion
        if( isSinglePushValid && get(rank_w8_b1, firstPushSquare) ) {
            addMove(move, encodeMove(pieceSquare, firstPushSquare, piece, q, 0, 0, 0, 0));
            addMove(move, encodeMove(pieceSquare, firstPushSquare, piece, r, 0, 0, 0, 0));
            addMove(move, encodeMove(pieceSquare, firstPushSquare, piece, b, 0, 0, 0, 0));
            addMove(move, encodeMove(pieceSquare, firstPushSquare, piece, n, 0, 0, 0, 0));
        } 
        // Just Push 
        else if( isSinglePushValid ) {
            addMove(move, encodeMove(pieceSquare, firstPushSquare, piece, 0, 0, 0, 0, 0));
        }

        // Double Push
        if( isDoublePushValid ) {
            addMove(move, encodeMove(pieceSquare, secondPushSquare, piece, 0, 0, 1, 0, 0));
        }

        if( enpassant != NO_SQUARE && get(attackLookup.pawn[side][pieceSquare], enpassant) ) {
            addMove(move, encodeMove(pieceSquare, enpassant, piece, 0, 0, 0, 1, 0));
        }
        
        // Pawn Attacks
        U64 attack = attackLookup.pawn[side][pieceSquare] & state->occupancy[!side];
        
        while( attack ){
            int attack_lsb = get_LSB_index(attack);

            // Promotion
            if( get(rank_w8_b1, attack_lsb) ){
                addMove(move, encodeMove(pieceSquare, attack_lsb, piece, q, 1, 0, 0, 0));
                addMove(move, encodeMove(pieceSquare, attack_lsb, piece, r, 1, 0, 0, 0));
                addMove(move, encodeMove(pieceSquare, attack_lsb, piece, b, 1, 0, 0, 0));
                addMove(move, encodeMove(pieceSquare, attack_lsb, piece, n, 1, 0, 0, 0));
            }
            else {
                addMove(move, encodeMove(pieceSquare, attack_lsb, piece, 0, 1, 0, 0, 0));
            }

            remove(attack, attack_lsb);            
        }

        remove(pawnBoard, pieceSquare);
    }

}