#include "helper.h"
#include "macros.h"
#include <string.h>


void parseFEN(gameState *state, char *fen)
{
    int square = 0;
    int index = 0;

    memset(state->board, 0ULL, sizeof(state->board));
    memset(state->occupancy, 0ULL, sizeof(state->occupancy));

    state->castle = 0;
    state->enpassant = NO_SQUARE;


    while( fen[index] != 32)
    {
        if(fen[index] >= '1' && fen[index] <= '8')
        {
            square += fen[index] - '0';
        }

        else if((fen[index] >= 'a' && fen[index] <= 'z') || (fen[index] >= 'A' && fen[index] <= 'Z'))
        {
            set(state->board[asciiToPieces[fen[index]]], square);
            square++;
        }

        index++;
    }


    index++;
    state->side = (fen[index] == 'w') ? WHITE : BLACK;

    index+=2; 
    printf("Index: %d\n", index);
    while(fen[index] != ' ') {
        switch(fen[index]) {
            case 'K': state->castle |= WK; break;
            case 'Q': state->castle |= WQ; break;
            case 'k': state->castle |= BK; break;
            case 'q': state->castle |= BQ; break;
            default: break;
        }
        index++;
    }
    
    printf("Castle: %d\n", state->castle);

    index++;
    if(fen[index] == '-'){
        state->enpassant = NO_SQUARE;
        index += 2;
    }
    else{
        state->enpassant = (8 - fen[index+1] + '0') * BOARD_SIZE + (fen[index] - 'a');
        index += 3;
    }



    for(int i=P; i<=K; i++){
        state->occupancy[WHITE] |= state->board[i];
    }

    for(int i=p; i<=k; i++){
        state->occupancy[BLACK] |= state->board[i];
    }

    state->occupancy[BOTH] = state->occupancy[BLACK] | state->occupancy[WHITE];
}