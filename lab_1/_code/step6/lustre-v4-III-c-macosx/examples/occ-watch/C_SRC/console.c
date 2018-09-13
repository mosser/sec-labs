
/*
Constants and functions of the screen handler

The files to include
*/

typedef char* string;
#include <stdio.h>
/*
#include <sgtty.h>
*/
#include <curses.h>
#include "MAIN.h"
#include "CONSOLE.h"
#include "DISPLAY.h"



/*
The screen coordinates of the positions to enhance
*/

short X_ENHANCE[] = {main3_col, main1_col+1, main2_col,main2_col+1,
		     mini1_col,mini2_col,alpha_col};
short Y_ENHANCE[] = {lower_line+1, lower_line+1, lower_line+1, lower_line+1,
		     upper_line+1, upper_line+1, upper_line+1};

/*
Ending
*/

void DISPLAY_END () {
	clear();
	refresh();
	endwin();
}

/* 
Screen initialization
*/

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

/*
Editing the watch
*/

New_Watch_O_display(disp)
DISPLAY_TYPE disp ;
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


/*
Leaving
*/

bye() {
	DISPLAY_END();
	exit(0);
}
