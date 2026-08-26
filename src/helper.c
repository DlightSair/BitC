#include "utils.h"
#include "header.h"


// FOR FINDING CONSTANT VALUES AND CREATING LOOKUPS

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



void displayNotFile()
{
    char charFile[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    for(int k = 0; k < BOARD_SIZE; k++)
    {
        U64 not_file = ~0ULL;

        for( int rank = 0; rank < BOARD_SIZE; rank++)
        {
            for( int file = 0; file < BOARD_SIZE; file++)
            {
                int square = rank*BOARD_SIZE + file;
                if( file == k){
                    remove(not_file, square);
                }
            }
            printf("\n");
        }

        printf("\n  NOT %c FILE\n\n", charFile[k]);
        printBitBoard( not_file );

    }
}



void displayTwoNotFile()
{

    U64 not_file = ~0ULL;

    for( int rank = 0; rank < BOARD_SIZE; rank++)
    {
        for( int file = 0; file < BOARD_SIZE; file++)
        {
            int square = rank*BOARD_SIZE + file;
            if( file == 6 || file == 7){
                remove(not_file, square);
            }
        }

        printf("\n");

    }

    printf("\n  NOT GH FILE\n\n");
    printBitBoard( not_file );

    
}


void print_relevent_occupancy(int piece)    // 1 for bishop, 0 for rook (FOR NOW)
{

    U64 (*maskAttack)(int) = (piece) ? maskBishopAttacks : maskRookAttacks;

    for( int rank = 0; rank < BOARD_SIZE; rank++){
        for(int file = 0; file < BOARD_SIZE; file++){
            int square = rank*BOARD_SIZE + file;

            printf("%d, ", count_bits(maskAttack(square)));
        }
        printf("\n");
    }
}