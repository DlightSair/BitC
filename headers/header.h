#ifndef HEADER_H
#define HEADER_H

#include "macros.h"

// HELPER.c
void printBoard(); // FOR COPY PASTE EASE
void displayNotFile();
void displayTwoNotFile();


// ATTACKTABLES.c
U64 getPawnAttack(int side, int board);
U64 getKnightAttack(int piece);


// INIT ATTACK TABLE
void init_reaper_moves(attackTables *attack);

// DISPLAY.C
void printBitBoard(U64 bitboard);


#endif