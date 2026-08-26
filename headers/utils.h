#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/*
    In this header

    -MACROS
    -STRUCT
    -ENUMS
    -CONSTANTS


*/



#define U64 unsigned long long
#define BOARD_SIZE 8
#define SIZE 64

// Operations MACROS
#define get(bitboard, square) (bitboard & (1ULL << square)) ? 1: 0
#define add(bitboard, square) (bitboard |= (1ULL << square))
#define remove(bitboard, square) (bitboard &= ~(1ULL << square))

#define count_bits(bitboard) __builtin_popcountll(bitboard)
#define get_LSB_index(bitboard) __builtin_ctzll(bitboard)



// STRUCT DATA TYPE FOR ATTACK TABLE

typedef struct 
{
    U64 pawn[2][SIZE];
    U64 knight[SIZE];
    U64 king[SIZE];

} attackTables;



// ENUMS

enum {
    WHITE,
    BLACK
};

enum {
    a8, b8, c8, d8, e8, f8, g8, h8, 
    a7, b7, c7, d7, e7, f7, g7, h7, 
    a6, b6, c6, d6, e6, f6, g6, h6, 
    a5, b5, c5, d5, e5, f5, g5, h5, 
    a4, b4, c4, d4, e4, f4, g4, h4, 
    a3, b3, c3, d3, e3, f3, g3, h3, 
    a2, b2, c2, d2, e2, f2, g2, h2, 
    a1, b1, c1, d1, e1, f1, g1, h1
};




// CONSTANTS

// GLOBAL VARIABLE FOR ATTACK LOOKUP
extern const attackTables attackLookup;


// Values gotten from helper.c : displayNotFile()

static const U64 notA = 18374403900871474942ULL;
static const U64 notB = 18302063728033398269ULL;
static const U64 notC = 18157383382357244923ULL;
static const U64 notD = 17868022691004938231ULL;
static const U64 notE = 17289301308300324847ULL;
static const U64 notF = 16131858542891098079ULL;
static const U64 notG = 13816973012072644543ULL;
static const U64 notH = 9187201950435737471ULL;

static const U64 notAB = 18229723555195321596ULL;
static const U64 notGH = 4557430888798830399ULL;

// LOOKUP

static const int rook_relevent_bit[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

static const int bishop_relevent_bit[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};


#endif