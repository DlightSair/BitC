#include "helper.h"

#define MAX_HISTORY 1024

// Hash of every position reached so far (game moves + current search path)
static U64 history[MAX_HISTORY];
static int historyCount = 0;

void clearHistory(void)
{
    historyCount = 0;
}

void pushHistory(U64 hash)
{
    if(historyCount < MAX_HISTORY){
        history[historyCount++] = hash;
    }
}

void popHistory(void)
{
    if(historyCount > 0) historyCount--;
}


static int isRepetition(const gameState *state)
{
    int current = historyCount - 1;
    int oldest = current - state->half;
    if(oldest < 0) oldest = 0;

    for(int i = current - 2; i >= oldest; i -= 2)
    {
        if(history[i] == history[current]){
            return 1;
        }
    }

    return 0;
}

static int isInsufficientMaterial(const gameState *state)
{
    if(state->board[P] || state->board[p]) return 0;
    if(state->board[R] || state->board[r]) return 0;
    if(state->board[Q] || state->board[q]) return 0;

    int minorPieces = count_bits(state->board[N] | state->board[n] |
                                 state->board[B] | state->board[b]);

    return minorPieces <= 1;
}

int isDraw(const gameState *state)
{
    if(state->half >= 100) return 1;
    if(isInsufficientMaterial(state)) return 1;

    return isRepetition(state);
}
