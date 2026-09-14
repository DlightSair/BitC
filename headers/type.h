#ifndef TYPE_H
#define TYPE_H

#include <stdint.h>
#include <inttypes.h>

#include "macros.h"


typedef uint64_t U64;
typedef uint32_t U32;


typedef struct 
{
    U64 board[12];
    U64 occupancy[3];
    int side;
    int castle;
    int enpassant;
    int half;
    int full;
} gameState;


// STRUCT DATA TYPE FOR ATTACK TABLE

// Final attack lookup table. 
typedef struct
{
    U64 pawn[2][SIZE];
    U64 knight[SIZE];
    U64 king[SIZE];
    U64 bishop[SIZE][512]; // 2^9
    U64 rook[SIZE][4096];  // 2^12

} attackTables;


// Relevant-occupancy masks per square (edges excluded).
typedef struct
{
    U64 bishop[SIZE];
    U64 rook[SIZE];

} attackMasks;


typedef struct
{
    int move[256];
    int count;
} moveList;




// ENUMS

enum {
    WHITE,
    BLACK,
    BOTH
};

enum {
    P, N, B, R, Q, K,
    p, n, b, r, q, k
};

enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Board squares, a8=0 ... h1=63
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, NO_SQUARE
};

enum {
    WK = 1, WQ = 2,
    BK = 4, BQ = 8
};


#endif