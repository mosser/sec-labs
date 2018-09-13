/*
Types and defined constants for the ALARM node
*/


/*
Types of the ALARM node and their copy functions

The type of alarm times
*/

typedef struct {int hours;
                int minutes;
                int mode12h;} ALARM_TIME_TYPE;

#define _cond_ALARM_TIME_TYPE(A,B,C) (A?B:C)

/*
The type of alarm positions is just integer
*/

typedef int ALARM_TIME_POSITION;

#define _ALARM_TIME_POSITION(X,Y) (*(X)=(Y))

#define _cond_ALARM_TIME_POSITION(A,B,C) (A?B:C)

/*
Defined constants of the ALARM node

The initial alarm position
*/

#define INITIAL_ALARM_POSITION 0

/*
The alarm duration (in seconds)
*/

#define ALARM_DURATION 30

