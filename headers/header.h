#ifndef HEADER_H
#define HEADER_H

#include "utils.h"

// HELPER.c
void printBoard(); // FOR COPY PASTE EASE
void displayNotFile();
void displayTwoNotFile();


// ATTACKTABLES.c
U64 maskPawnAttacks(int side, int board);
U64 maskKnightAttacks(int piece);
U64 maskKingAttacks(int piece);
U64 maskBishopAttacks(int piece);
U64 maskRookAttacks(int piece);



U64 getRookAttacks(int piece, U64 block);
U64 getBishopAttacks(int piece, U64 block);


// INIT ATTACK TABLE
void init_reaper_moves(attackTables *attack);
void init_attack_lookup();



// DISPLAY.C
void printBitBoard(U64 bitboard);


#endif