#include "macros.h"


void printBoard()
{
    char charFile[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    for( int rank = 0; rank < BOARD_SIZE; rank++)
    {
        for( int file = 0; file < BOARD_SIZE; file++)
        {
            printf("%c%d, ", charFile[file], BOARD_SIZE - rank);
        }

        printf("\n");

    }
}