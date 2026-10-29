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


static const int pieceValue[12] = {100, 300, 350, 500, 900, 10000,
                                   100, 300, 350, 500, 900, 10000};

#define CAPTURE_BONUS   10000
#define PROMOTION_BONUS  9000


static int getVictimPiece(const gameState *state, int target)
{
    int startPiece = (state->side == WHITE) ? p : P;
    int endPiece = (state->side == WHITE) ? k : K;

    for(int piece = startPiece; piece <= endPiece; piece++)
    {
        if(get_bit(state->board[piece], target)){
            return piece;
        }
    }

    return (state->side == WHITE) ? p : P;
}


static int scoreMove(const gameState *state, int move)
{
    if(getCapture(move)){
        int victim = getVictimPiece(state, getTarget(move));
        return CAPTURE_BONUS + 10 * pieceValue[victim] - pieceValue[getPiece(move)];
    }

    if(getProm(move)){
        return PROMOTION_BONUS;
    }

    return 0;
}


static void pickBestMove(moveList *moves, int *scores, int index)
{
    int bestIndex = index;

    for(int i = index + 1; i < moves->count; i++)
    {
        if(scores[i] > scores[bestIndex]){
            bestIndex = i;
        }
    }

    int tempMove = moves->move[index];
    moves->move[index] = moves->move[bestIndex];
    moves->move[bestIndex] = tempMove;

    int tempScore = scores[index];
    scores[index] = scores[bestIndex];
    scores[bestIndex] = tempScore;
}

static int quiescence(gameState *state, int alpha, int beta, SearchInfo *info)
{
    info->nodes++;

    int standPat = (state->side == WHITE) ?
        evaluate(state) : -evaluate(state);

    if(standPat >= beta) return beta;
    if(standPat > alpha) alpha = standPat;

    moveList moves = {.count = 0};
    generateMoves(state, &moves);

    int scores[256];
    for(int i=0; i < moves.count; i++){
        scores[i] = scoreMove(state, moves.move[i]);
    }

    gameState saved = *state;

    for(int i=0; i < moves.count; i++)
    {
        pickBestMove(&moves, scores, i);
        int move = moves.move[i];

        if(!scores[i]){
            break;
        }

        if(!makeMove(state, move)){
            continue;
        }

        int score = -quiescence(state, -beta, -alpha, info);
        *state = saved;

        if(score >= beta) return beta;
        if(score > alpha) alpha = score;
    }

    return alpha;
}

static int negamax(gameState *state, int alpha, int beta, int depth, int ply, SearchInfo *info)
{

    if(!depth){
        return quiescence(state, alpha, beta, info);
    }

    info->nodes++;

    moveList moves = {.count = 0};
    generateMoves(state, &moves);

    int scores[256];
    for(int i=0; i < moves.count; i++){
        scores[i] = scoreMove(state, moves.move[i]);
    }

    gameState saved = *state;
    int legal = 0;

    for(int i=0; i < moves.count; i++)
    {
        pickBestMove(&moves, scores, i);
        int move = moves.move[i];

        if(!makeMove(state, move)){
            continue;
        }
        legal++;

        int score = -negamax(state, -beta, -alpha, depth-1, ply+1, info);
        *state = saved;

        if(score > alpha){
            alpha = score;

            if(ply == 0) info->bestMove = move;
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
