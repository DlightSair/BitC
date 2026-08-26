#ifndef HEADER_H
#define HEADER_H

#include "utils.h"

/*

    WILL ORGANIZE IT LATER :>
    this mess for now


*/

// HELPER.c
void printBoard(); // FOR COPY PASTE EASE
void displayNotFile();
void displayTwoNotFile();
void print_relevent_occupancy(int piece);


// ATTACKTABLES.c
U64 maskPawnAttacks(int side, int board);
U64 maskKnightAttacks(int piece);
U64 maskKingAttacks(int piece);
U64 maskBishopAttacks(int piece);
U64 maskRookAttacks(int piece);



U64 getRookAttacks(int piece, U64 block);
U64 getBishopAttacks(int piece, U64 block);


// OCCUPANCY

U64 set_occupancy(int index, int bits_in_board, U64 attack_board);




// INIT ATTACK TABLE
void init_reaper_moves(attackTables *attack);
void init_attack_lookup();



// DISPLAY.C
void printBitBoard(U64 bitboard);


// RANDOM NUMBER
void change_random_number(unsigned int *number);

#endif