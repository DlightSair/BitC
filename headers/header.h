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
void print_relevent_occupancy(int square);


// ATTACKTABLES.c
U64 maskPawnAttacks(int side, int board);
U64 maskKnightAttacks(int square);
U64 maskKingAttacks(int square);
U64 maskBishopAttacks(int square);
U64 maskRookAttacks(int square);



U64 getRookAttacks(int square, U64 block);
U64 getBishopAttacks(int square, U64 block);


// OCCUPANCY

U64 set_occupancy(int index, U64 attack_board);



// INIT ATTACK TABLE
void init_reaper_moves(attackTables *attack);
void init_attack_lookup();


// MAGIC NUMBERS 
void init_magicNumbers();


// DISPLAY.C
void printBitBoard(U64 bitboard);


// RANDOM NUMBER
U32 get_random_U32();
U64 get_random_U64();
U64 get_magnic_number_candidate();




#endif