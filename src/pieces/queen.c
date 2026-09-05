#include "helper.h"
#include "pieces.h"

U64 getRookAttacks(int square, U64 block)
{
    return getRookAttacks(square, block) | getBishopAttacks(square, block);
}