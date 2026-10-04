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

    char *test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parseFEN(&state, test);
    
    generateMoves(&state, &move);
    printBoard(state);
    displayMove(&move);

    U64 node = 0;

    START_MEASURE_TIMER(start_time)
    perft_driver(state, 6, &node);
    END_MEASURE_TIMER(end_time)

    printf("Node: %d\n", node);
    DISPLAY_MEASURED_TIMER(start_time, end_time)

    


    return 0;
}