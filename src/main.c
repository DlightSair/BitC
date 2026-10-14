#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"
#include "macros.h"
#include <windows.h>
#include "evaluation.h"


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

    uciLoop(&state);

    return 0;
}