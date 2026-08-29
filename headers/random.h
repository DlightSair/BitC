#ifndef RANDOM_H
#define RANDOM_H

#include "type.h"

// RANDOM NUMBER

U32 get_random_U32(void);    // xorshift32, deterministic seed
U64 get_random_U64(void);
U64 get_magnic_number_candidate(void);   // candidate for magic search


#endif