#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>

#define U64 unsigned long long
#define BOARD_SIZE 8



// Operations MACROS
#define get(bitboard, square) (bitboard & (1ULL << square)) ? 1: 0
#define add(bitboard, square) (bitboard |= (1ULL << square))
#define remove(bitboard, square) (bitboard &= ~(1ULL << square))


// ENUMS

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


#endif