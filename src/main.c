#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"
#include "macros.h"


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

    char *test = "r3k2r/pppp1ppp/2n2n2/4P3/1B6/2N2N2/PPPP1PpP/R1BQK2R b KQkq - 4 5";
    parseFEN(&state, test);

    printBoard(state);
    generateMoves(&state, &move);

    displayMove(&move);
 
    return 0;
}