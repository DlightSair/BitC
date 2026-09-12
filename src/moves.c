#include "helper.h"
#include "type.h"
#include "pieces.h"
#include "macros.h"
#include "constants.h"




// Pseudo-Legal moves ---- checkLegalMove will be made later
void generateMoves(gameState state)
{
    int sourceSquare;
    int targetSquare;

    U64 bitboard;
    U64 attacks;

    switch (state.side)
    {
    case WHITE:
        generatePawnMoves(state.board[P], state.occupancy[BOTH], state.enpassant, state.side);

        break;

    
    case BLACK:
        generatePawnMoves(state.board[p], state.occupancy[BOTH], state.enpassant, state.side);

        break;
    }


}