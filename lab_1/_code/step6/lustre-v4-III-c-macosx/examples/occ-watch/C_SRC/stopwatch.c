/*
Constants and functions of the STOPWATCH
*/



typedef char* string;
#include "MAIN.h"
#include "STOPWATCH.h"
#include "CONST.h"

/* The assignment procedure */

void _STOPWATCH_TIME_TYPE(X,Y)
char* X; STOPWATCH_TIME_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(STOPWATCH_TIME_TYPE);
	while(size--)*P++=*Q++;
}



/*
The initial stopwatch time
*/

STOPWATCH_TIME_TYPE INITIAL_STOPWATCH_TIME = {0, 0, 0};

/*
Testing whether the stopwatch time is multiple of 10 minutes

For the sake of simulation, this test will be true whenever the time is multiple of 1 minute
*/

_bool IS_ZERO_MOD_10_MN (st)
STOPWATCH_TIME_TYPE st; {

   return ((st.hsec==0) && (st.seconds == 0) && (st.minutes %1 == 0));
}

/*
Incrementing a stopwatch time
*/

STOPWATCH_TIME_TYPE INCREMENT_STOPWATCH_TIME (pst)
STOPWATCH_TIME_TYPE pst; {

/* The increment depends on the time-unit. 
   Remember that time_unit is 1/TIME-SCALE
*/

   pst.hsec+= 100/TIME_SCALE;
   if (pst.hsec== 100) {
      pst.hsec= 0;
      pst.seconds += 1;
      if (pst.seconds == 60) {
         pst.seconds = 0;
         pst.minutes += 1;
         if (pst.minutes == 60) {
            pst.minutes = 0;
            pst.hours += 1;
            if (pst.hours == 24) {
               pst.hours = 0;
            }
         }
      }
   }
   return(pst);
}

/*
Comparing two stopwatch times
*/

_bool NEQ_STOPWATCH_TIME (sw1,sw2)
STOPWATCH_TIME_TYPE sw1,sw2; {
   _bool eq;
   eq=	(sw1.hours == sw2.hours) &
	(sw1.minutes == sw2.minutes) &
	(sw1.seconds == sw2.seconds) &
	(sw1.hsec == sw2.hsec);
   return(!eq);
}
