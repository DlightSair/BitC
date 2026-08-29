#include "helper.h"
#include "random.h"


U32 current = 1804289383;


U32 get_random_U32(void)
{
    U32 number = current;

    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;

    current = number;
    return number;
}

// Returns Random Unsigned Long Long (U64)
U64 get_random_U64(void)
{
    return (U64)get_random_U32() | ((U64)(get_random_U32()) << 32);
}

// Returns Candidate for Magic Number (U64)
U64 get_magnic_number_candidate(void)
{
    return get_random_U64() & get_random_U64() & get_random_U64();
}