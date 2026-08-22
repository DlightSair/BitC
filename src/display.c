#include "macros.h"
#include "header.h"



void printBitBoard(U64 bitboard)
{
    printf("\n");

    for( int rank = 0 ; rank < BOARD_SIZE ; rank++)
    {
        for( int file = 0 ; file < BOARD_SIZE ; file++)
        {
            int square = rank * BOARD_SIZE + file;

            if(!file) printf("  %d | ", BOARD_SIZE - rank);

            printf("%d ", get( bitboard , square ));

        }

        printf("\n");

    }

    printf("     -----------------\n");
    printf("      a b c d e f g h\n");
    printf("\n  BitBoard: %llu\n\n", bitboard);

}