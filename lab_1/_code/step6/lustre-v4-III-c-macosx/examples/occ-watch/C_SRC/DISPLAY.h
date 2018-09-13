/*
Types and defined constants for the DISPLAYHANDLER node


Types of the DISPLAYHANDLER node and their copy functions


The main display type
*/

typedef struct {char hours[4]; /* should be 3, but bugs in some C compilers */
                char minutes[4];
                char seconds [4];
                char timemode[4]; } MAIN_DISPLAY_TYPE;

#define _cond_MAIN_DISPLAY_TYPE(A,B,C) (A?B:C)

/*
The mini display type
*/

typedef struct {char fst[3];
                char sep[2];
                char snd[3]; } MINI_DISPLAY_TYPE;

#define _cond_MINI_DISPLAY_TYPE(A,B,C) (A?B:C)


/*
The status type
*/

typedef struct {_bool alarm_set;
		_bool chime_set;
		_bool stopwatch_running;
		_bool stopwatch_lapping;} STATUS_TYPE;

#define _cond_STATUS_TYPE(A,B,C) (A?B:C)

/*
The display position type 
(could be different from watch position and alarm position types)
*/

typedef int DISPLAY_POSITION;


#define _DISPLAY_POSITION(X,Y) (*(X)=(Y))
#define _cond_DISPLAY_POSITION(A,B,C) (A?B:C)

/*
The type of button labels
*/

typedef struct {char ul_lab[14];
                char ll_lab[14];
                char ur_lab[4];
                char lr_lab[12];} LABELS_TYPE;

/*
The display type
*/

typedef struct{MAIN_DISPLAY_TYPE main;
		MINI_DISPLAY_TYPE mini;
		string alpha;
		STATUS_TYPE status;
		DISPLAY_POSITION enhanced;
		LABELS_TYPE lab;} DISPLAY_TYPE;


#define _cond_DISPLAY_TYPE(A,B,C) (A?B:C)
