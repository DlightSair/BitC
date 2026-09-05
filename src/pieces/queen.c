#include "helper.h"
#include "pieces.h"

U64 getQueenAttacks(int square, U64 block)
{
    return getRookAttacks(square, block) | getBishopAttacks(square, block);
}