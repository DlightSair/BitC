#include "type.h"
#include <windows.h>

U64 getCurrentTimer()
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (U64) t.QuadPart;
}