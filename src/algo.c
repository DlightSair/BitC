#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"
#include "macros.h"
#include "evaluation.h"
#include <windows.h>

#define INF  50000
#define MATE 49000

typedef struct {
    int bestMove;
    U64 nodes;
} SearchInfo;

static int negamax(gameState *state, int alpha, int beta, int depth, int ply, SearchInfo *info)
{
    if(!depth){
        info->nodes++;
        return (state->side == WHITE) ?
            evaluate(state) : -evaluate(state);
    }

    moveList moves = {.count = 0};
    generateMoves(state, &moves);

    gameState saved = *state;
    int legal = 0;

    for(int i=0; i < moves.count; i++)
    {
        if(!makeMove(state, moves.move[i])){
            continue;
        }
        legal++;

        int score = -negamax(state, -beta, -alpha, depth-1, ply+1, info);
        *state = saved;

        if(score > alpha){
            alpha = score;

            if(ply == 0) info->bestMove = moves.move[i];
            if(alpha >= beta) break;
        }
    }

    if(!legal){
        int king = (state->side == WHITE) ? K : k;
        int inCheck = isSquareAttacked(state, get_LSB_index(state->board[king]), !state->side);
        return inCheck ? -MATE + ply : 0;
    }

    return alpha;
}

int getBestMove(gameState *state, int depth)
{

    gameState copy = *state;
    SearchInfo info = { .bestMove = -1, .nodes = 0 };

    U64 start = getCurrentTimer();
    negamax(&copy, -INF, INF, depth, 0, &info);
    U64 end = getCurrentTimer();

    printf("info nodes %llu nps %.0f\n", info.nodes, info.nodes / time_elapsed(start, end));

    return info.bestMove;
}
