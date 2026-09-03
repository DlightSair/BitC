#include "helper.h"

static int* setBoardState(U64 bitboard[], int board[])
{
    for(int i=0; i<64; i++) board[i] = -1;

    for(int piece=0; piece < 12; piece++)
    {
        while(bitboard[piece])
        {
            int LSB = get_LSB_index(bitboard[piece]);
            board[LSB] = piece;
            remove(bitboard[piece], LSB);
        }
    }
}

void printBoard(U64 bitboard[])
{
    int board[64];
    setBoardState(bitboard, board);

    printf("\n");

    for(int rank=0; rank < BOARD_SIZE; rank++)
    {
        for(int file=0; file < BOARD_SIZE; file++)
        {
            int square = rank*BOARD_SIZE + file;
            if(!file) printf("  %d | ", BOARD_SIZE - rank);

            if( board[square] == -1){
                printf(". ");
            }else{
                printf("%c ", asciiPiece[board[square]]);
            }
        }
        printf("\n");
    }
    printf("     -----------------\n");
    printf("      a b c d e f g h\n\n");
}



// Displays Bitboard (Unsigned Long Long in binary 1 for Occupied 0 For Not Occupied)
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