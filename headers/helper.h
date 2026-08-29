#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#include "type.h"
#include "macros.h"
#include "constants.h"

// HELPER

void printBoard(void);          // a1-h8 coordinate grid, used for calcuating constants
void displayNotFile(void);      // prints notA..notH, used for calcuating constants
void displayTwoNotFile(void);   // prints notGH, used for calcuating constants
void print_relevent_occupancy(int piece);   // used for calcuating constants


U64 set_occupancy(int index, U64 attack_board);   // index-th blocker arrangement, for table generation

void printBitBoard(U64 bitboard);


#endif