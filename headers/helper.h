#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#include "type.h"
#include "macros.h"
#include "constants.h"

// HELPER

void printBoardIndex(void);          // a1-h8 coordinate grid, used for calcuating constants
void displayNotFile(void);      // prints notA..notH, used for calcuating constants
void displayTwoNotFile(void);   // prints notGH, used for calcuating constants
void print_relevent_occupancy(int piece);   // used for calcuating constants


U64 set_occupancy(int index, U64 attack_board);   // index-th blocker arrangement, for table generation

// DISPLAY
void printBitBoard(U64 bitboard);
void printBoard(gameState state);
void printAttackedBoard(const gameState *state);
void displayMove(const moveList *move);


// Parse FEN
void parseFEN(gameState *state, char *fen);


// Moves
void generateMoves(const gameState *state);
void addMove(moveList *move, int newMove);


// Attack
int isSquareAttacked(const gameState *s, int square, int side);


#endif