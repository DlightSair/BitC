#include "type.h"
#include <windows.h>
#include <stdio.h>

U64 getCurrentTimer(void)
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return (U64) t.QuadPart;
}

double time_elapsed(U64 start, U64 end)
{
    LARGE_INTEGER MEASURE_TIMER_FREQUENCY;     
    QueryPerformanceFrequency(&MEASURE_TIMER_FREQUENCY);

    double time_sec =          
        (double) (end - start) /
        (double) MEASURE_TIMER_FREQUENCY.QuadPart; 

    return time_sec;
}


void DISPLAY_MEASURED_TIME(U64 TIMER_MEASURE_START, U64 TIMER_MEASURE_END)
{                                                      
    double TIMER_MEASURED_SECONDS = time_elapsed(TIMER_MEASURE_START, TIMER_MEASURE_END);  
                                                                                        
    if(TIMER_MEASURED_SECONDS < 1e-6)                                                      
        printf("MEASURED TIMER: %.3f ns\n", TIMER_MEASURED_SECONDS * 1e9);                 
                                                                                        
    else if(TIMER_MEASURED_SECONDS < 1e-3)                                                 
        printf("MEASURED TIMER: %.3f us\n", TIMER_MEASURED_SECONDS * 1e6);                 
                                                                                        
    else if(TIMER_MEASURED_SECONDS < 1)                                                    
        printf("MEASURED TIMER: %.3f ms\n", TIMER_MEASURED_SECONDS * 1e3);                 
                                                                                        
    else                                                                                   
        printf("MEASURED TIMER: %.3f s\n", TIMER_MEASURED_SECONDS);                 

}