/*
The stopwatch time type and its copy function
*/

typedef struct {int hours;
                int minutes;
                int seconds;
                int hsec; } STOPWATCH_TIME_TYPE;

#define _cond_STOPWATCH_TIME_TYPE(A,B,C) (A?B:C)
