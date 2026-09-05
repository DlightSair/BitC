#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"


// GLOBAL VARIBLE ATTACK LOOKUP 
attackTables attackLookup;
attackMasks maskAttacks;

int main()
{
    init_attack_lookup();

    gameState state;

    char *startingPostionFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parseFEN(&state, startingPostionFEN);

 
    printBoard(state);
    printAttackedBoard(state);

    return 0;
}