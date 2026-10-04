#include "type.h"
#include "helper.h"
#include "constants.h"
#include "macros.h"
#include "string.h"

void perft_driver(gameState state, int depth, U64 *nodes)
{
    if(depth == 0){
        (*nodes)++;
        return;
    }

    moveList moves = {.count = 0};
    generateMoves(&state, &moves);

    gameState temp = state;

    for(int i=0; i < moves.count; i++)
    {
        if(!makeMove(&state, moves.move[i])){
            continue;
        }

        perft_driver(state, depth-1, nodes);
        state = temp;
    }
}