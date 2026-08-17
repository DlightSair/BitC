#include "macros.h"
#include "display.h"

int main()
{
    U64 bitBoard = 0ULL;

    add(bitBoard, e2);
    add(bitBoard, e5);
    remove(bitBoard, e2);

    printBitBoard(bitBoard);

    return 0;
}