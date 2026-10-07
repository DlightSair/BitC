#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"
#include "macros.h"
#include "windows.h"


// GLOBAL VARIBLE ATTACK LOOKUP 
attackTables attackLookup;
attackMasks maskAttacks;

int main()
{
    init_attack_lookup();

    gameState state;
    moveList move = {
        .count = 0
    };

    char *startingPostionFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parseFEN(&state, startingPostionFEN);

    char *test = "1r2k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P1RPP/R2Q2K1 w kq - 0 1";
    parseFEN(&state, test);
    
    printBoard(state);

    generateMoves(&state, &move);
    displayMove(&move);


    return 0;
}