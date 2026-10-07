#include "helper.h"
#include "macros.h"
#include "constants.h"
#include <string.h>

int UCI_to_move(const gameState *state, char *UCI_move)
{
    int source = UCI_move[0] - 'a' + (8 - UCI_move[1] + '0') * 8;
    int target = UCI_move[2] - 'a' + (8 - UCI_move[3] + '0') * 8;

    int move_val = -1;

    moveList move = {
        .count = 0
    };

    generateMoves(state, &move);

    for(int i=0; i < move.count; i++)
    {
        if( source == getSource(move.move[i]) && target == getTarget(move.move[i]))
        {
            if(getProm(move.move[i]))
            {
                if((getProm(move.move[i]) == asciiToPieces[UCI_move[4]])){
                    move_val = move.move[i];
                    break;
                }
            }
            else
            {
                move_val = move.move[i];
                break;
            }
        }
    }

    return move_val;
}