
#include <curses.h>
#include <stdio.h>
#include "New_Watch.h"
#include "New_Watch_ext.h"

/*----------------------------------------------------
!!!!!!!!!!! IMPORTANT PARAMETERS !!!!!!!!!!!!!!!!!!!
-------------------------------------------------------
TIME SCALE is the number of time units per second.
It must divide 100.
-----------------------------------------------------*/
#define TIME_SCALE 10


/*----------------------------------------------------
SCREEN MANIPULATION
-----------------------------------------------------*/
#define  _XW  40
#define  _YW  10
#define  upper_line  (_YW-2)
#define  medium_line  (_YW+1)
#define  lower_line  (_YW+3)
#define  alpha_col  (_XW-6)
#define  main1_col  (_XW-1)
#define  main2_col  (_XW+2)
#define  main3_col  (_XW+5)
#define  mini1_col  (_XW+2)
#define  mini2_col  (_XW+5)
#define llabels_col (_XW-20)
#define rlabels_col (_XW+9)
short X_ENHANCE[] = {main3_col, main1_col+1, main2_col,main2_col+1,
           mini1_col,mini2_col,alpha_col};
short Y_ENHANCE[] = {lower_line+1, lower_line+1, lower_line+1, lower_line+1,
           upper_line+1, upper_line+1, upper_line+1};

void DISPLAY_INIT () {
   initscr();
   clear();
   noecho();
   crmode();
   move(_YW-5, _XW-5);
   addstr("LUSTRE watch");
   move(_YW - 4, _XW - 7);
   addstr("________________");
   move(_YW - 3, _XW - 7);
   addstr("|      |       |");
   move(_YW - 2, _XW - 7);
   addstr("|      |   :   |"); /* Upper line */
   move(_YW - 1, _XW - 7);
   addstr("|      |       |");
   move(_YW , _XW - 7);
   addstr("|______________|");
   move(_YW +1, _XW - 7);
   addstr("|              |"); /* Medium line */
   move(_YW +2, _XW - 7);
   addstr("|              |");
   move(_YW  + 3, _XW - 7);
   addstr("|       :      |"); /* Lower line */
   move(_YW +4, _XW - 7);
   addstr("|              |");
   move(_YW +5, _XW - 7);
   addstr("|______________|");
   refresh();
}

void DISPLAY_END () {
   clear();
   refresh();
   endwin();
}

/*----------------------------------------------------
OUTPUT FUNCTION DECLARATIONS
-----------------------------------------------------*/
void New_Watch_O_display(void* dummy, DISPLAY_TYPE disp)
{
	int hpos;
/* Main display */
	move(lower_line,main1_col);
	addstr(disp.main.hours);
	move(lower_line,main2_col);
	addstr(disp.main.minutes);
	move(lower_line,main3_col);
	addstr(disp.main.seconds);
/* 24H/AM-PM, Stopwatch or Alarm status */
	move(medium_line,alpha_col);
	addstr(disp.main.timemode);
/* Mini display */
	move(upper_line,mini1_col);
	addstr(disp.mini.fst);
	move(upper_line,mini2_col);
	addstr(disp.mini.snd);
/* Alpha display */
	move(upper_line,alpha_col);
	addstr(disp.alpha);
/* LAP and RUN status of the stopwatch */
	move(upper_line,alpha_col+3);
	if (disp.status.stopwatch_running) addstr("RUN");
	else addstr("   ");
	move(upper_line+1,alpha_col+3);
	if (disp.status.stopwatch_lapping) addstr("LAP");
	else addstr("   ");
/* Alarm set, Chime set status */
	move(medium_line,mini1_col);
	if (disp.status.alarm_set) addstr("AL");
	else addstr("  ");
	move(medium_line,mini2_col);
	if (disp.status.chime_set) addstr("CH");
	else addstr("  ");
/* Position enhancing */
	for (hpos=0; hpos<=7; hpos++)
	{	move(Y_ENHANCE[hpos],X_ENHANCE[hpos]);
		if (hpos == disp.enhanced) addstr("^");
		else addstr(" ");
	}
/* Button labels */
   move(upper_line,llabels_col);
   addstr(disp.lab.ul_lab);
   move(lower_line,llabels_col);
   addstr(disp.lab.ll_lab);
   move(upper_line,rlabels_col);
   addstr(disp.lab.ur_lab);
   move(lower_line,rlabels_col);
   addstr(disp.lab.lr_lab); 
	refresh();
}
void New_Watch_O_beep(void* dummy, _integer bell)
{
    for (;bell>0;bell--) {printf("\007");}
}

/*----------------------------------------------------
EXTERNAL FUNCTION DECLARATIONS
-----------------------------------------------------*/

void LABELS(
   LABELS_TYPE* res,
   _boolean mw, _boolean ms, _boolean ma, _boolean msw, _boolean msa
) {
   if (msw) {
/* mode is SET_WATCH */
      strcpy(res->ul_lab ,"to watch mode");
      strcpy(res->ll_lab ,"next position");
      strcpy(res->ur_lab ,"   ");
      strcpy(res->lr_lab ,"set       ");
   } else if (mw) {
/* mode is WATCH */
      strcpy(res->ul_lab ," to set watch");
      strcpy(res->ll_lab ," to stopwatch");
      strcpy(res->ur_lab ,"   ");
      strcpy(res->lr_lab ,"24/12H    ");
   } else if (msa) {
/* mode is SET_ALARM */
      strcpy(res->ul_lab ,"     to alarm");
      strcpy(res->ll_lab ,"next position");
      strcpy(res->ur_lab ,"   ");
      strcpy(res->lr_lab ,"set       ");
   } else if (ma) {
/* mode is ALARM */
      strcpy(res->ul_lab ," to set alarm");
      strcpy(res->ll_lab ,"     to watch");
      strcpy(res->ur_lab ,"set");
      strcpy(res->lr_lab ,"chime     ");
   } else {
/* mode is STOPWATCH */
      strcpy(res->ul_lab ,"             ");
      strcpy(res->ll_lab ,"     to alarm");
      strcpy(res->ur_lab ,"lap");
      strcpy(res->lr_lab ,"start/stop");
   }
}

void WATCH_TO_DISPLAY_POS(DISPLAY_POSITION* res, WATCH_TIME_POSITION wtp){
	*res = wtp;
}

void ALARM_TO_DISPLAY_POS(DISPLAY_POSITION* res, ALARM_TIME_POSITION atp){
	*res = atp+1;
}

void STATUS(
   STATUS_TYPE* res,
   _boolean alarm_is_set,
   _boolean chime_is_set,
   _boolean stopwatch_running,
   _boolean stopwatch_lapping
){
   res->alarm_set = alarm_is_set;
   res->chime_set = chime_is_set;
   res->stopwatch_running = stopwatch_running;
   res->stopwatch_lapping = stopwatch_lapping;
}

void MAKE_DISPLAY(
   DISPLAY_TYPE* res,
   MAIN_DISPLAY_TYPE main,
   MINI_DISPLAY_TYPE mini,
   string alpha,
   STATUS_TYPE status,
   DISPLAY_POSITION enhanced,
   LABELS_TYPE lab
){
   _assign_MAIN_DISPLAY_TYPE(&(res->main), main);
   _assign_MINI_DISPLAY_TYPE(&(res->mini), mini);
   res->alpha=alpha;
   _assign_STATUS_TYPE(&(res->status), status);
   res->enhanced = enhanced;
   _assign_LABELS_TYPE(&(res->lab), lab);
}

void WATCH_TIME_TO_MAIN_DISPLAY(
   MAIN_DISPLAY_TYPE* res,
   WATCH_TIME_TYPE wt
){
   static MAIN_DISPLAY_TYPE maindt;
   static int hours;
/* in AM-PM mode, the time is converted */
   if (wt.mode12h) {
     hours = wt.hours % 12;
     if (!hours) hours=12;
   } else {
     hours=wt.hours;
   }
   sprintf(maindt.hours,"%2d",hours);
   sprintf(maindt.minutes,"%02d",wt.minutes);
   sprintf(maindt.seconds,"%02d",wt.seconds);
/* The 24H/AM-PM mode */
   if (wt.mode12h) {
      if (wt.hours>11) strcpy(maindt.timemode,"PM ");
      else strcpy(maindt.timemode,"AM ");
   } else strcpy(maindt.timemode,"24H");
   * res = maindt;
}

void STOPWATCH_TIME_TO_MAIN_DISPLAY(
   MAIN_DISPLAY_TYPE* res,
   STOPWATCH_TIME_TYPE st
){
   static MAIN_DISPLAY_TYPE maindt;
/* when the time is less than an hour, it is displyed in minutes,
seconds, 1/100sec., othrwise it is displayed in hours, minutes, seconds */
   if (st.hours) {
      sprintf(maindt.hours,"%2d",st.hours);
      sprintf(maindt.minutes,"%02d",st.minutes);
      sprintf(maindt.seconds,"%02d",st.seconds);
      strcpy(maindt.timemode,"   ");
   } else {
      sprintf(maindt.hours,"%2d",st.minutes);
      sprintf(maindt.minutes,"%02d",st.seconds);
      sprintf(maindt.seconds,"%02d",st.hsec);
      strcpy(maindt.timemode,"   ");
   };
   *res = maindt;
}

void ALARM_TIME_TO_MAIN_DISPLAY(
	MAIN_DISPLAY_TYPE* res,
	ALARM_TIME_TYPE at
) {
   static MAIN_DISPLAY_TYPE maindt;
   static int hours;
/* in AM-PM mode, the time is converted */
   if (at.mode12h) {
     hours = at.hours % 12;
     if (!hours) hours=12;
   } else {
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
   *res = maindt;
}


void WATCH_DATE_TO_MINI_DISPLAY(
	MINI_DISPLAY_TYPE* res,
	WATCH_TIME_TYPE wt
) {
   static MINI_DISPLAY_TYPE minidt;
   sprintf(minidt.fst,"%2d",wt.month+1);
   sprintf(minidt.snd,"%2d",wt.day);
   *res = minidt;
}

void WATCH_TIME_TO_MINI_DISPLAY(
	MINI_DISPLAY_TYPE* res,
	WATCH_TIME_TYPE wt
) {
   static MINI_DISPLAY_TYPE minidt;
   if (wt.mode12h) sprintf(minidt.fst,"%2d",wt.hours % 12);
   else sprintf(minidt.fst,"%2d",wt.hours);
   sprintf(minidt.snd,"%02d",wt.minutes);
   *res = (minidt);
}

static char * day_names [7] = {"SU","MO","TU","WE","TH","FR","SA"};

void WATCH_DAY_TO_ALPHA_DISPLAY(
	string* res,
	WATCH_TIME_TYPE wt
) {
	*res = (day_names[wt.day_in_week]);
}

void TOGGLE_24H_IN_ALARM_MODE(
	ALARM_TIME_TYPE* res,
	ALARM_TIME_TYPE pat
) {
   pat.mode12h = ! pat.mode12h;
   *res = (pat);
}

void SET_ALARM_TIME(
   ALARM_TIME_TYPE* res,
	ALARM_TIME_TYPE pat,
	ALARM_TIME_POSITION atp
) {
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
   *res = (pat);
}

void NEXT_ALARM_TIME_POSITION(
   ALARM_TIME_POSITION* res,
	ALARM_TIME_POSITION atp
) {
	*res = ((atp+1)%3);
}

void COMPARE_WATCH_ALARM_TIME(
   _boolean* res,
	WATCH_TIME_TYPE wt,
	ALARM_TIME_TYPE at
) {
	*res = (wt.seconds==0 && at.hours==wt.hours && at.minutes==wt.minutes);
}

static short monthlength [] = {31,29,31,30,31,30,31,31,30,31,30,31};

void INCREMENT_WATCH_TIME(
	WATCH_TIME_TYPE* res,
	WATCH_TIME_TYPE pwt
){
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
   *res = (pwt);
}

void TOGGLE_24H_IN_WATCH_MODE(
	WATCH_TIME_TYPE* res,
	WATCH_TIME_TYPE pwt
) {
   pwt.mode12h = ! pwt.mode12h;
   *res =(pwt);
}

void CONFIRM_TIME(
	WATCH_TIME_TYPE* res,
	WATCH_TIME_TYPE wt
) {
   if (wt.day > monthlength[wt.month]) {
      wt.day = wt.day - monthlength[wt.month];
            wt.month = (wt.month+1)%12;
   };
   *res = (wt);
}

void INCREMENT_WATCH_TIME_IN_SET_MODE(
   WATCH_TIME_TYPE* res,
	WATCH_TIME_TYPE pwt,
	WATCH_TIME_POSITION wtp
) {
   pwt.seconds += 1;
   if (pwt.seconds == 60) {
      pwt.seconds = 0;
      if (wtp == 3) {
         *res = (pwt); /* in set minutes mode */
         return;
      }
      if (wtp == 2) {  /* set 10 minutes mode */
         if (pwt.minutes % 10 == 9) pwt.minutes -= 9;
         else pwt.minutes +=1;
         *res = (pwt);
         return;
      }
      pwt.minutes += 1;
      if (pwt.minutes == 60) {
         pwt.minutes = 0;
         if (wtp == 1) {
            *res = (pwt); /* set hours mode */
            return;
         }
         pwt.hours += 1;
         if (pwt.hours == 24) {
            pwt.hours = 0;
            if (wtp == 4 || wtp == 6) {
               *res = (pwt); /* set day mode */
               return;
            }
            pwt.day +=1;
            pwt.day_in_week = (pwt.day_in_week+1)%7;
            if (pwt.day > monthlength[pwt.month]) {
               pwt.day = 1;
               if (wtp == 5) {
                  *res = (pwt);   /* set month mode */
                  return;
               }
               pwt.month = (pwt.month+1) % 12;
            }
         }
      }
   }
   *res = (pwt);
}

void NEXT_WATCH_TIME_POSITION(
   WATCH_TIME_POSITION* res,
	WATCH_TIME_POSITION wtp
) {
	*res = ((wtp+1)%7);
}

void SET_WATCH_TIME(
   WATCH_TIME_TYPE* res,
	WATCH_TIME_TYPE pwt,
	WATCH_TIME_POSITION wtp
) {
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
   *res = (pwt);
}


void IS_O_CLOCK(
	_boolean* res,
	WATCH_TIME_TYPE wt
) {
   *res = ((wt.seconds == 0) && (wt.minutes==0));
}

void INCREMENT_STOPWATCH_TIME(
   STOPWATCH_TIME_TYPE* res,
	STOPWATCH_TIME_TYPE pst
) {
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
   *res = (pst);
}

void IS_ZERO_MOD_10_MN(
   _boolean* res,
	STOPWATCH_TIME_TYPE st
) {
   *res = ((st.hsec==0) && (st.seconds == 0) && (st.minutes %1 == 0));
}

/*----------------------------------------------------
MAIN PROGRAM 
-----------------------------------------------------*/
