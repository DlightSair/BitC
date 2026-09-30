#include "helper.h"

static void setBoardState(U64 bitboard[], int board[])
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

static char* getCastleString(int castle, char castleStr[])
{
    int c = 0;
    
    if( castle & WK ) castleStr[c++] = 'K';
    if( castle & WQ ) castleStr[c++] = 'Q';
    if( castle & BK ) castleStr[c++] = 'k';
    if( castle & BQ ) castleStr[c++] = 'q';

    if(c==0) castleStr[c++] = '-';
    castleStr[c] = '\0';
}

void printBoard(gameState state)
{
    int board[64];
    setBoardState(state.board, board);

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

    char castleStr[5];
    getCastleString(state.castle, castleStr);

    printf("     -----------------\n");
    printf("      a b c d e f g h\n\n");
    printf("    Side        : %s\n", state.side == WHITE? "White" : "Black");
    printf("    Enpassant   : %s\n", squareToString[state.enpassant]);
    printf("    Castle      : %s\n\n", castleStr);
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


void displayMove(const moveList *move)
{
    printf("\n   | S  | T  | P | Prom | Cap | D  | En | Cas | Move  \n");
    printf("   ----------------------------------------------------\n");

    for(int i=0; i<move->count; i++)
    {
        printf("   | %s | %s | %c |  %c   |  %d  | %d  | %d  | %d   |  %d\n",
            squareToString[getSource(move->move[i])],
            squareToString[getTarget(move->move[i])],
            asciiPiece[getPiece(move->move[i])],
            (getProm(move->move[i]) ? asciiPiece[getProm(move->move[i])] : '-'),
            getCapture(move->move[i]),
            getDouble(move->move[i]),
            getEnpassant(move->move[i]),
            getCastle(move->move[i]),
            move->move[i]
        );
    }
    printf("\n");
}