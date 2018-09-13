/*
Types and defined constants for the WATCH node
*/

/*
The watch time type and its copy function
*/

typedef struct {int day_in_week;
                int month;
                int day;
                int hours;
                int minutes;
                int seconds;
                int mode12h;} WATCH_TIME_TYPE;

#define _cond_WATCH_TIME_TYPE(A,B,C) (A?B:C)

/*
The watch time position type and its copy function
*/

typedef int WATCH_TIME_POSITION;

#define _WATCH_TIME_POSITION(X,Y) (*(X)=(Y))
#define _cond_WATCH_TIME_POSITION(A,B,C) (A?B:C)

/*
Defined Constants of the WATCH node

The initial watch time position
*/

#define INITIAL_WATCH_POSITION 0

/*
The initial watch time will be set by the main program
*/

WATCH_TIME_TYPE INITIAL_WATCH_TIME;

