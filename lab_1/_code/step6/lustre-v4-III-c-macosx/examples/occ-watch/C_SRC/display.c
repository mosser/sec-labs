
/*
Constants, functions of the DISPLAY HANDLER

Files to include
*/

typedef char* string;
#include "MAIN.h"
#include "DISPLAY.h"
#include "WATCH.h"
#include "STOPWATCH.h"
#include "ALARM.h"

/* The assignment procedures */

void _MAIN_DISPLAY_TYPE(X,Y)
char* X; MAIN_DISPLAY_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(MAIN_DISPLAY_TYPE);
	while(size--)*P++=*Q++;
}

void _MINI_DISPLAY_TYPE(X,Y)
char* X; MINI_DISPLAY_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(MINI_DISPLAY_TYPE);
	while(size--)*P++=*Q++;
}

void _DISPLAY_TYPE(X,Y)
char* X; DISPLAY_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(DISPLAY_TYPE);
	while(size--)*P++=*Q++;
}

void _STATUS_TYPE(X,Y)
char* X; STATUS_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(STATUS_TYPE);
	while(size--)*P++=*Q++;
}

void _LABELS_TYPE(X,Y)
char* X; LABELS_TYPE Y; {
	register char* P=X; 
	register char* Q= (char*)(&Y);
	register int size;
	size = sizeof(LABELS_TYPE);
	while(size--)*P++=*Q++;
}

void _string(X,Y)
char **X, *Y;{
       *X = Y;
}

/*
Displaying a watch time on the main display
*/

MAIN_DISPLAY_TYPE WATCH_TIME_TO_MAIN_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MAIN_DISPLAY_TYPE maindt;
   static hours;

/* in AM-PM mode, the time is converted */

   if (wt.mode12h) {
     hours = wt.hours % 12;
     if (!hours) hours=12;
   }
   else {
     hours=wt.hours;
   }
   sprintf(maindt.hours,"%2d",hours);
   sprintf(maindt.minutes,"%02d",wt.minutes);
   sprintf(maindt.seconds,"%02d",wt.seconds);

/* The 24H/AM-PM mode */

   if (wt.mode12h) {
      if (wt.hours>11)
        strcpy(maindt.timemode,"PM ");
        else strcpy(maindt.timemode,"AM ");}
   else strcpy(maindt.timemode,"24H");
   return(maindt);
}
                           
/*
Displaying a watch time on the mini display
(in stopwatch and alarm modes)
*/

MINI_DISPLAY_TYPE WATCH_TIME_TO_MINI_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MINI_DISPLAY_TYPE minidt;
   if (wt.mode12h) sprintf(minidt.fst,"%2d",wt.hours % 12);
   else sprintf(minidt.fst,"%2d",wt.hours);
   sprintf(minidt.snd,"%02d",wt.minutes);
   return(minidt);
}

/*
Displaying a date on the mini display 
*/

MINI_DISPLAY_TYPE WATCH_DATE_TO_MINI_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   static MINI_DISPLAY_TYPE minidt;
   sprintf(minidt.fst,"%2d",wt.month+1);
   sprintf(minidt.snd,"%2d",wt.day);
   return(minidt);
}


/*
Displaying a day in week (alphabetic display)
*/

char * day_names [7] = {"SU","MO","TU","WE","TH","FR","SA"};

char * WATCH_DAY_TO_ALPHA_DISPLAY (wt)
WATCH_TIME_TYPE wt; {
   return(day_names[wt.day_in_week]);
}

/*
Getting a display position from a watch time position 
(it is the identity)
*/

DISPLAY_POSITION WATCH_TO_DISPLAY_POS (wtp)
WATCH_TIME_POSITION wtp; {
   return(wtp);
}

/*
Displaying a stopwatch time on the main display 
*/

MAIN_DISPLAY_TYPE STOPWATCH_TIME_TO_MAIN_DISPLAY (st)
STOPWATCH_TIME_TYPE st; {
   static MAIN_DISPLAY_TYPE maindt;

/* when the time is less than an hour, it is displyed in minutes,
   seconds, 1/100sec., othrwise it is displayed in hours, minutes, seconds */

   if (st.hours) {
      sprintf(maindt.hours,"%2d",st.hours);
      sprintf(maindt.minutes,"%02d",st.minutes);
      sprintf(maindt.seconds,"%02d",st.seconds);
      strcpy(maindt.timemode,"   ");
   }
   else {
      sprintf(maindt.hours,"%2d",st.minutes);
      sprintf(maindt.minutes,"%02d",st.seconds);
      sprintf(maindt.seconds,"%02d",st.hsec);
      strcpy(maindt.timemode,"   ");
   };
   return(maindt);
}

/*
Displaying an alarm time on the main display 
*/

MAIN_DISPLAY_TYPE ALARM_TIME_TO_MAIN_DISPLAY (at)
ALARM_TIME_TYPE at; {
   static MAIN_DISPLAY_TYPE maindt;
   static hours;

/* in AM-PM mode, the time is converted */

   if (at.mode12h) {
     hours = at.hours % 12;
     if (!hours) hours=12;
   }
   else {
     hours=at.hours;
   }
   sprintf(maindt.hours,"%2d",hours);
   sprintf(maindt.minutes,"%02d",at.minutes);
   sprintf(maindt.seconds,"  ");

/* The 24H/AM-PM mode */

   if (at.mode12h) {
     if (at.hours>11)
        strcpy(maindt.timemode,"PM ");
        else strcpy(maindt.timemode,"   ");
     } else strcpy(maindt.timemode,"24H");
   return(maindt);
}

/*
From alarm time position to display position
(Identity)
*/

ALARM_TO_DISPLAY_POS (atp)
ALARM_TIME_POSITION atp; {
   return(atp+1);
}

/*
The button labels, from the mode
*/


LABELS_TYPE LABELS(mw,ms,ma,msw,msa)
_bool mw, ms, ma, msw, msa; {
	LABELS_TYPE l;
        if (msw) {

/* mode is SET_WATCH */

 		strcpy(l.ul_lab ,"to watch mode");
          	strcpy(l.ll_lab ,"next position");
		strcpy(l.ur_lab ,"   ");
		strcpy(l.lr_lab ,"set       ");
	}
	else if (mw) {

/* mode is WATCH */

 		strcpy(l.ul_lab ," to set watch");
          	strcpy(l.ll_lab ," to stopwatch");
		strcpy(l.ur_lab ,"   ");
		strcpy(l.lr_lab ,"24/12H    ");
	}
	else if (msa) {

/* mode is SET_ALARM */

 		strcpy(l.ul_lab ,"     to alarm");
          	strcpy(l.ll_lab ,"next position");
		strcpy(l.ur_lab ,"   ");
		strcpy(l.lr_lab ,"set       ");
	}
	else if (ma) {

/* mode is ALARM */

 		strcpy(l.ul_lab ," to set alarm");
          	strcpy(l.ll_lab ,"     to watch");
		strcpy(l.ur_lab ,"set");
		strcpy(l.lr_lab ,"chime     ");
	}
	else {

/* mode is STOPWATCH */

 		strcpy(l.ul_lab ,"             ");
          	strcpy(l.ll_lab ,"     to alarm");
		strcpy(l.ur_lab ,"lap");
		strcpy(l.lr_lab ,"start/stop");
	};
	return(l);
}
		
		
DISPLAY_TYPE MAKE_DISPLAY(main,mini,alpha,status,enhanced,lab)
MAIN_DISPLAY_TYPE main;
MINI_DISPLAY_TYPE mini;
string alpha;
STATUS_TYPE status;
DISPLAY_POSITION enhanced;
LABELS_TYPE lab;
{ 	DISPLAY_TYPE display;
	_MAIN_DISPLAY_TYPE(&(display.main), main);
	_MINI_DISPLAY_TYPE(&(display.mini), mini);
	display.alpha=alpha;
	_STATUS_TYPE(&(display.status), status);
	display.enhanced = enhanced;
	_LABELS_TYPE(&(display.lab), lab);
	return display;
}
		
STATUS_TYPE STATUS(alarm_is_set, chime_is_set, stopwatch_running,
stopwatch_lapping)
_bool alarm_is_set, chime_is_set, stopwatch_running, stopwatch_lapping;
{	STATUS_TYPE status;
	status.alarm_set = alarm_is_set;
	status.chime_set = chime_is_set;
	status.stopwatch_running = stopwatch_running;
	status.stopwatch_lapping = stopwatch_lapping;
	return status;
}
