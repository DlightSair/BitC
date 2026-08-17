#include "macros.h"

inline static int get_bit(U64 bitboard, int square)
{
    return ( (bitboard) & (1ULL << square) ) ? 1 : 0;
}



void printBitBoard(U64 bitboard)
{
    printf("\n");

    for( int rank = 0 ; rank < BOARD_SIZE ; rank++)
    {
        for( int file = 0 ; file < BOARD_SIZE ; file++)
        {
            int square = rank * BOARD_SIZE + file;

            printf("%d ", get_bit( bitboard , square ));

        }

        printf("\n");

    }

    printf("\n");
}