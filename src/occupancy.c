#include "helper.h"


// Returns (index)th configuration of block among all possible configurations 
U64 set_occupancy(int index, U64 attack_board)
{
    U64 occupancy = 0ULL;
    int bits_in_board = count_bits(attack_board);

    for(int i = 0; i < bits_in_board; i++){
        int LSB_1 = get_LSB_index(attack_board);
        remove(attack_board, LSB_1);

        if( index & (1ULL << i)){
            set(occupancy, LSB_1);
        }
    }

    return occupancy;
}