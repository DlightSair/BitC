#ifndef HEADER_H
#define HEADER_H

#include "macros.h"

// HELPER.c
void printBoard(); // FOR COPY PASTE EASE
void displayNotFile();
void displayTwoNotFile();


// ATTACKTABLES.c
U64 maskPawnAttacks(int side, int board);
U64 maskKnightAttacks(int piece);
U64 maskKingAttacks(int piece);
U64 maskBishopAttacks(int piece);


// INIT ATTACK TABLE
void init_reaper_moves(attackTables *attack);

// DISPLAY.C
void printBitBoard(U64 bitboard);


#endif