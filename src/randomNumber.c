#include "utils.h"
#include "header.h"

void change_random_number(unsigned int *number)
{
    // XORSHIFT32 
    *number ^= *number << 13;
    *number ^= *number >> 17;
    *number ^= *number << 5;
}