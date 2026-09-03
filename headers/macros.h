#ifndef MACROS_H
#define MACROS_H



#define BOARD_SIZE 8
#define SIZE 64

// Operations MACROS

// Get bit on (square) position in bitboard
#define get(bitboard, square) ((bitboard) & (1ULL << (square))) ? 1: 0    

// Change bit on (square) position to 1
#define set(bitboard, square) ((bitboard) |= (1ULL << (square)))             

// Change bit on (square) position to 0
#define remove(bitboard, square) ((bitboard) &= ~(1ULL << (square)))        



#define count_bits(bitboard) __builtin_popcountll(bitboard)      // Total Number of 1 Bit in Bitboard
#define get_LSB_index(bitboard) __builtin_ctzll(bitboard)        // index of LSB, undefined if 0

#endif