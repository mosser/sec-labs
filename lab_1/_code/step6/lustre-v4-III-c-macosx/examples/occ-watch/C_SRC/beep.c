
/*
Functions of the TIME_BEEP node

The files to include
*/

typedef char* string;
#include "MAIN.h"
#include "BEEP.h"
#include "WATCH.h"
#include "STOPWATCH.h"

/*
Testing whether the time is exactly on the hour
*/

_bool IS_O_CLOCK(wt)
WATCH_TIME_TYPE wt; {
   return ((wt.seconds == 0) && (wt.minutes==0));
}

/* 
Beeping
*/

New_Watch_O_beep(bell)
BEEP_TYPE bell; {
  for (;bell>0;bell--) 
     {printf("\007");}
  return(bell);
}
