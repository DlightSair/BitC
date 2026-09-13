#ifndef PIECES_H
#define PIECES_H

#include "type.h"

U64 maskPawnAttacks(int side, int square);  
void generatePawnMoves(U64 pawnBoard, U64 occupancy[], int enpassant, int side);


U64 maskKnightAttacks(int square);

U64 maskKingAttacks(int square);
void generateKingMoves(const gameState *state);


U64 maskBishopAttacks(int square);   // relevant-occupancy mask, edges excluded
U64 calculateBishopAttacks(int square, U64 block);   // brute force for getting Bishop Attack
U64 getBishopAttacks(int square, U64 block);   // magic lookup for getting Bishop Attack


U64 maskRookAttacks(int square);     // relevant-occupancy mask, edges excluded
U64 calculateRookAttacks(int square, U64 block);     // brute force for getting Rook Attack
U64 getRookAttacks(int square, U64 block);     // magic lookup for getting Rook Attack


U64 getQueenAttacks(int square, U64 block);

#endif