
/*
Constants and functions of the WATCH

The files to include :
*/

typedef char* string;
#include "MAIN.h"
#include "WATCH.h"
#include <time.h>

/*
The assignment function
*/

void _WATCH_TIME_TYPE(X,Y)
char* X; WATCH_TIME_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(WATCH_TIME_TYPE);
	while(size--)*P++=*Q++;
}

/*
The initial watch time

The constant INITIAL_WATCH_TIME is initialized in the main program, 
using the function GET_INITIAL_WATCH_TIME.
*/


WATCH_TIME_TYPE GET_INITIAL_WATCH_TIME () {
   WATCH_TIME_TYPE wt;
   struct tm *ptm;
   long tloc;
   time(&tloc);
   ptm=localtime(&tloc);
   wt.day_in_week = ptm->tm_wday;
   wt.month = ptm->tm_mon;
   wt.day = ptm->tm_mday;
   wt.hours = ptm->tm_hour;
   wt.minutes = ptm->tm_min;
   wt.seconds = ptm->tm_sec;
   wt.mode12h = 0;
   return(wt);
}

/*
A month length table
*/

static short monthlength [] = {31,29,31,30,31,30,31,31,30,31,30,31};

/*
Functions of the WATCH


Going to the next watch time position
*/

NEXT_WATCH_TIME_POSITION (wtp)
WATCH_TIME_POSITION wtp; {
   return((wtp+1)%7);
}

/*
Incrementing the time in watch-mode
*/


WATCH_TIME_TYPE INCREMENT_WATCH_TIME (pwt)
WATCH_TIME_TYPE pwt;
{
   pwt.seconds += 1;
   if (pwt.seconds == 60) {
      pwt.seconds = 0;
      pwt.minutes += 1;
      if (pwt.minutes == 60) {
         pwt.minutes = 0;
         pwt.hours += 1;
         if (pwt.hours == 24) {
            pwt.hours = 0;
            pwt.day +=1;
            pwt.day_in_week = (pwt.day_in_week+1)%7;
            if (pwt.day > monthlength[pwt.month]) {
               pwt.day = 1;
               pwt.month = (pwt.month+1) % 12;
            }
         }
      }
   }
   return(pwt);
}

/*
Incrementing the time in set-watch mode

The incrementation is done only up to the watch time position being currently
set.
*/

WATCH_TIME_TYPE INCREMENT_WATCH_TIME_IN_SET_MODE (pwt,wtp)
WATCH_TIME_TYPE pwt;
WATCH_TIME_POSITION wtp; {
   pwt.seconds += 1;
   if (pwt.seconds == 60) {
      pwt.seconds = 0;
      if (wtp == 3) return (pwt); /* in set minutes mode */
      if (wtp == 2) {  /* set 10 minutes mode */
         if (pwt.minutes % 10 == 9) pwt.minutes -= 9;
         else pwt.minutes +=1;
         return (pwt);
      }
      pwt.minutes += 1;
      if (pwt.minutes == 60) {
         pwt.minutes = 0;
         if (wtp == 1) return (pwt); /* set hours mode */
         pwt.hours += 1;
         if (pwt.hours == 24) {
            pwt.hours = 0;
            if (wtp == 4 || wtp == 6) return (pwt); /* set day mode */
            pwt.day +=1;
            pwt.day_in_week = (pwt.day_in_week+1)%7;
            if (pwt.day > monthlength[pwt.month]) {
               pwt.day = 1;
               if (wtp == 5) return (pwt);   /* set month mode */
               pwt.month = (pwt.month+1) % 12;
            }
         }
      }
   }
   return(pwt);
}

/*
Toggling the 24H/AM-PM status 
*/

WATCH_TIME_TYPE TOGGLE_24H_IN_WATCH_MODE (pwt)
WATCH_TIME_TYPE pwt; {
   pwt.mode12h = ! pwt.mode12h;
   return(pwt);
}


/*
Setting a watch time at a given position
*/


WATCH_TIME_TYPE SET_WATCH_TIME (pwt,wtp)
WATCH_TIME_TYPE pwt; 
WATCH_TIME_POSITION wtp; {
   switch (wtp) {
      case 0 : /* seconds */
         pwt.seconds=0;
         break;
      case 1 : /* hours */
         pwt.hours = (pwt.hours+1) % 24;
         break;
      case 2 : /* 10 minutes */
         pwt.minutes = (pwt.minutes >= 50 ? pwt.minutes-50
                                            : pwt.minutes+10 );
         break;
      case 3 : /* minutes */
         pwt.minutes = (pwt.minutes %10 == 9
                               ? pwt.minutes-9
                               : pwt.minutes+1);
         break;
      case 4 : /* month */
         pwt.month = (pwt.month+1)%12;
         break;
      case 5 : /* day */
         pwt.day = (pwt.day >= monthlength[pwt.month]
                               ? 1
                               : pwt.day+1 );
         break;
      case 6 : /* day in week */
         pwt.day_in_week = (pwt.day_in_week+1) % 7;
         break;
   }
   return(pwt);
}


/* 
Checking a watch time for calendar inconsistencies 
*/

WATCH_TIME_TYPE CONFIRM_TIME (wt)
WATCH_TIME_TYPE wt; {
	if (wt.day > monthlength[wt.month]) {
		wt.day = wt.day - monthlength[wt.month];
         	wt.month = (wt.month+1)%12;
	};
	return(wt);
}

/*
Comparing two watch times
*/

_bool NEQ_WATCH_TIME (wt1,wt2)
WATCH_TIME_TYPE wt1,wt2;  {
   _bool eq;
   eq = (wt1.day_in_week == wt2.day_in_week) &
	(wt1.month == wt2.month) &
	(wt1.day == wt2.day) &
	(wt1.hours == wt2.hours) &
	(wt1.minutes == wt2.minutes) &
	(wt1.seconds == wt2.seconds) &
	(wt1.mode12h == wt2.mode12h) ;
  return(!eq);
}

/*
Comparing two watch positions
*/

_bool NEQ_WATCH_POSITION (pos1,pos2)
WATCH_TIME_POSITION pos1,pos2; {
   return(pos1 != pos2 );
}
