#include "helper.h"
#include "pieces.h"
#include "init.h"
#include "constants.h"
#include "macros.h"

const int material_score_mg[6] = {100, 300, 350, 500, 1000, 0};
const int material_score_eg[6] = {100, 300, 350, 500, 1000, 0};

const int phase_weight[6] = {0, 1, 1, 2, 4, 0};
#define MAX_PHASE 24

#define TEMPO_BONUS 10

const int positional_score[6][64] = 
{
    // PAWN
    {
    0,    0,   0,   0,   0,   0,   0,   0,
    30,  30,  30,  40,  40,  30,  30,  30,
    20,  20,  20,  30,  30,  30,  20,  20,
    10,  10,  10,  20,  20,  10,  10,  10,
     5,   5,  10,  20,  20,   5,   5,   5,
     0,   0,   0,   5,   5,   0,   0,   0,
     10, 10,  10, -10, -10,  10,  10,  10,
     0,   0,   0,   0,   0,   0,   0,   0
    },

    // KNIGHT
    {
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,  10,  10,   0,   0,  -5,
    -5,   5,  20,  20,  20,  20,   5,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,   5,  20,  10,  10,  20,   5,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5, -10,   0,   0,   0,   0, -10,  -5
    },

    // BISHOP
    {
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,  10,  10,   0,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,  10,   0,   0,   0,   0,  10,   0,
     0,  30,   0,   0,   0,   0,  30,   0,
     0,   0, -10,   0,   0, -10,   0,   0

    },

    // ROOK
    {
    50,  50,  50,  50,  50,  50,  50,  50,
    50,  50,  50,  50,  50,  50,  50,  50,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,   0,  20,  20,   0,   0,   0

    },

    // QUEEN
    {
   -20, -10, -10,  -5,  -5, -10, -10, -20,
   -10,   0,   0,   0,   0,   0,   0, -10,
   -10,   0,   5,   5,   5,   5,   0, -10,
    -5,   0,   5,   5,   5,   5,   0,  -5,
    -5,   0,   5,   5,   5,   5,   0,  -5,
   -10,   5,   5,   5,   5,   5,   0, -10,
   -10,   0,   5,   0,   0,   0,   0, -10,
   -20, -10, -10,  -5,  -5, -10, -10, -20
    },

    {
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -20, -30, -30, -40, -40, -30, -30, -20,
   -10, -20, -20, -20, -20, -20, -20, -10,
    20,  20,   0,   0,   0,   0,  20,  20,
    20,  30,  10,   0,   0,  10,  30,  20
    }
};

const int pawn_endgame_score[64] =
{
      0,   0,   0,   0,   0,   0,   0,   0,
    100, 100, 100, 100, 100, 100, 100, 100,
     60,  60,  60,  60,  60,  60,  60,  60,
     35,  35,  35,  35,  35,  35,  35,  35,
     20,  20,  20,  20,  20,  20,  20,  20,
     10,  10,  10,  10,  10,  10,  10,  10,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0
};

const int king_endgame_score[64] =
{
    -30, -20, -15, -10, -10, -15, -20, -30,
    -20, -10,  -5,   0,   0,  -5, -10, -20,
    -15,  -5,  10,  15,  15,  10,  -5, -15,
    -10,   0,  15,  20,  20,  15,   0, -10,
    -10,   0,  15,  20,  20,  15,   0, -10,
    -15,  -5,  10,  15,  15,  10,  -5, -15,
    -20, -15,   0,   0,   0,   0, -15, -20,
    -30, -20, -15, -15, -15, -15, -20, -30
};


const int mirror_score[128] =
{
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};


static int getEndgamePositional(int type, int square)
{
    if(type == PAWN) return pawn_endgame_score[square];
    if(type == KING) return king_endgame_score[square];

    return positional_score[type][square];
}


// Score from White's POV
int evaluate(const gameState *state)
{
    int middlegame = 0;
    int endgame = 0;
    int phase = 0;

    for(int piece = P; piece <= k; piece++)
    {
        int type = (piece <= K) ? piece : piece - 6;
        int sign = (piece <= K) ? 1 : -1;

        U64 board_copy = state->board[piece];

        phase += count_bits(board_copy) * phase_weight[type];

        while(board_copy){
            int lsb = get_LSB_index(board_copy);

            int square = (piece <= K) ? lsb : mirror_score[lsb];

            middlegame += sign * (material_score_mg[type] + positional_score[type][square]);
            endgame    += sign * (material_score_eg[type] + getEndgamePositional(type, square));

            clear_bit(board_copy, lsb);
        }
    }

    if(phase > MAX_PHASE) phase = MAX_PHASE;   // promotions can add extra pieces

    int score = (middlegame * phase + endgame * (MAX_PHASE - phase)) / MAX_PHASE;

    score += (state->side == WHITE) ? TEMPO_BONUS : -TEMPO_BONUS;

    return score;
}
