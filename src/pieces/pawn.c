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


void generatePawnMoves(const gameState *state)
{

//    U64 singlePush = shiftBitbaord(pawnBoard, 8 - 16*side) 
//        & (~occupancy);
//
//    U64 doublePush = shiftBitbaord(singlePush, 8 - 16*side) 
//        & (~occupancy) 
//        & (0x00000000FF000000ULL << (8 * side));
    int side = state->side;
    U64 pawnBoard = state->board[(side == WHITE) ? P : p];
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
            printf("Promotion %s: %s\n", squareToString[pieceSquare], squareToString[firstPushSquare]);
        } 
        // Just Push 
        else if( isSinglePushValid ) {
            printf("SinglePush %s: %s\n", squareToString[pieceSquare], squareToString[firstPushSquare]);
        }

        // Double Push
        if( isDoublePushValid ) {
            printf("DoublePush %s: %s\n", squareToString[pieceSquare], squareToString[secondPushSquare]);
        }

        if( enpassant != NO_SQUARE && get(attackLookup.pawn[side][pieceSquare], enpassant) ) {
            printf("EnPassant %s: %s\n", squareToString[pieceSquare], squareToString[enpassant]);
        }
        
        // Pawn Attacks
        U64 attack = attackLookup.pawn[side][pieceSquare] & state->occupancy[!side];
        
        while( attack ){
            int attack_lsb = get_LSB_index(attack);

            // Prootion
            if( get(rank_w8_b1, attack_lsb) ){
                printf("Pawn Promotion/Capture %s: %s\n", squareToString[pieceSquare], squareToString[attack_lsb]);
            }
            else {
                printf("Pawn Capture %s: %s\n", squareToString[pieceSquare], squareToString[attack_lsb]);
            }

            remove(attack, attack_lsb);            
        }

        remove(pawnBoard, pieceSquare);
    }

}