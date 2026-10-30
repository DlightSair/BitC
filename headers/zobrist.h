#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "type.h"

extern U64 pieceKeys[12][64];
extern U64 castleKeys[16];
extern U64 enpassantKeys[65];
extern U64 sideKey;

void initZobrist(void);
U64 generateHash(const gameState *state);

#endif
