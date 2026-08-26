#include "header.h"
#include "utils.h"


U64 set_occupancy(int index, int bits_in_board, U64 attack_board)
{
    U64 occupancy = 0ULL;

    for(int i = 0; i < bits_in_board; i++){
        int LSB_1 = get_LSB_index(attack_board);
        remove(attack_board, LSB_1);

        if( index & (1ULL << i)){
            add(occupancy, LSB_1);
        }
    }

    return occupancy;
}