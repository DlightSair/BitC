#include "helper.h"
#include "zobrist.h"

U64 pieceKeys[12][64];
U64 castleKeys[16];
U64 enpassantKeys[65];      
U64 sideKey;

static U64 zobristState = 0x9E3779B97F4A7C15ULL;

static U64 nextKey(void)
{
    zobristState += 0x9E3779B97F4A7C15ULL;

    U64 key = zobristState;
    key = (key ^ (key >> 30)) * 0xBF58476D1CE4E5B9ULL;
    key = (key ^ (key >> 27)) * 0x94D049BB133111EBULL;

    return key ^ (key >> 31);
}

void initZobrist(void)
{
    for(int piece = 0; piece < 12; piece++){
        for(int square = 0; square < 64; square++){
            pieceKeys[piece][square] = nextKey();
        }
    }

    for(int castle = 0; castle < 16; castle++){
        castleKeys[castle] = nextKey();
    }

    for(int square = 0; square < 64; square++){
        enpassantKeys[square] = nextKey();
    }
    enpassantKeys[NO_SQUARE] = 0ULL;

    sideKey = nextKey();
}

U64 generateHash(const gameState *state)
{
    U64 hash = 0ULL;

    for(int piece = P; piece <= k; piece++)
    {
        U64 board = state->board[piece];

        while(board){
            int square = get_LSB_index(board);
            hash ^= pieceKeys[piece][square];
            clear_bit(board, square);
        }
    }

    hash ^= castleKeys[state->castle];
    hash ^= enpassantKeys[state->enpassant];

    if(state->side == BLACK) hash ^= sideKey;

    return hash;
}
