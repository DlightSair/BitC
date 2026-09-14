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

    char *test = "r3k2r/ppppQppp/2n2n2/8/1B2P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 5";
    parseFEN(&state, test);

    addMove(&move, encodeMove(e1, e2, P, 0, 0, 0, 1, 0));
    addMove(&move, encodeMove(e1, d5, q, 0, 0, 0, 0, 1));
    addMove(&move, encodeMove(d1, e2, K, 0, 1, 1, 1, 0));
    displayMove(&move);
 
    return 0;
}