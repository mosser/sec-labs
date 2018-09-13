
/*
constants, functions, and procedures of the ALARM node

Files to include
*/

typedef char* string;
#include "MAIN.h"
#include "ALARM.h"

#include "WATCH.h"

/*
Constants of the ALARM module

The constant ALARM_DURATION is defined in the ALARM.h file using a 
#define statement.


The initial alarm time

The alarm is initially set at 00:00, in 24H mode
*/

ALARM_TIME_TYPE INITIAL_ALARM_TIME = {0,0,0};

/* The assignment procedure */

void _ALARM_TIME_TYPE(X,Y)
char* X; ALARM_TIME_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(ALARM_TIME_TYPE);
	while(size--)*P++=*Q++;
}


/*
Functions of the ALARM node

Comparing an alarm time to a watch time 
*/

_bool COMPARE_WATCH_ALARM_TIME (wt,at)
WATCH_TIME_TYPE wt; 
ALARM_TIME_TYPE at; {
   return(wt.seconds==0 && at.hours==wt.hours && at.minutes==wt.minutes);
}

/*
Going to the next alarm time position
*/

NEXT_ALARM_TIME_POSITION (atp) {
   return((atp+1)%3);
}

/*
Setting an alarm time at current position
*/

ALARM_TIME_TYPE SET_ALARM_TIME (pat,atp)
ALARM_TIME_TYPE pat; {
   switch (atp) {
      case 0 : /* hours */
         pat.hours = (pat.hours+1) % 24;
         break;
      case 1 : /* 10 minutes */
         pat.minutes = (pat.minutes >= 50 ? pat.minutes-50
                                            : pat.minutes+10 );
         break; 
      case 2 : /* minutes */
         pat.minutes = (pat.minutes %10 == 9
                               ? pat.minutes-9
                               : pat.minutes+1);
         break;
   }
   return(pat);
}

/*
Toggling the 24H/AM-PM mode in an alarm time
*/

ALARM_TIME_TYPE TOGGLE_24H_IN_ALARM_MODE (pat)
ALARM_TIME_TYPE pat; {
   pat.mode12h = ! pat.mode12h;
   return(pat);
}

/*
Comparing two alarm times
*/

_bool NEQ_ALARM_TIME (at1,at2)
ALARM_TIME_TYPE at1,at2;  {
   _bool eq;
   eq=	(at1.hours == at2.hours) &
	(at1.minutes == at2.minutes) &
	(at1.mode12h == at2.mode12h);
   return(!eq);
}

/*
Comparing two alarm positions
*/

_bool NEQ_ALARM_POSITION (pos1,pos2)
ALARM_TIME_POSITION pos1,pos2; {
   return(pos1 != pos2);
}
