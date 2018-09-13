
/*----------------------------------------------------
TYPE DECLARATIONS
------------------------------------------------------
NB: no need of _eq_XX nor _ne_xXX functions
NB: _assign_XX and _cond_XX can be inlined
-----------------------------------------------------*/

/*----------------------------------------------------
string TYPE
-----------------------------------------------------*/
typedef char* string;
#define _cond_string(A,B,C) (A?B:C)
#define _assign_string(X,Y) (*(X)=(Y))

/*----------------------------------------------------
MAIN DISPLAY TYPE
-----------------------------------------------------*/
typedef struct {
   char hours[4]; /* should be 3, but bugs in some C compilers */
   char minutes[4];
   char seconds [4];
   char timemode[4];
} MAIN_DISPLAY_TYPE;
#define _cond_MAIN_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_MAIN_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
MINI DISPLAY TYPE
-----------------------------------------------------*/

typedef struct {
   char fst[3];
   char sep[2];
   char snd[3];
} MINI_DISPLAY_TYPE;
#define _cond_MINI_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_MINI_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
STATUS TYPE
-----------------------------------------------------*/

typedef struct {
   _boolean alarm_set;
   _boolean chime_set;
   _boolean stopwatch_running;
   _boolean stopwatch_lapping;
} STATUS_TYPE;
#define _cond_STATUS_TYPE(A,B,C) (A?B:C)
#define _assign_STATUS_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
DISPLAY POSITION TYPE
-----------------------------------------------------*/

typedef int DISPLAY_POSITION;
#define _cond_DISPLAY_POSITION(A,B,C) (A?B:C)
#define _assign_DISPLAY_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
TYPE OF BUTTON LABELS
-----------------------------------------------------*/

typedef struct {
   char ul_lab[14];
   char ll_lab[14];
   char ur_lab[4];
   char lr_lab[12];
} LABELS_TYPE;
#define _cond_LABELS_TYPE(A,B,C) (A?B:C)
#define _assign_LABELS_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
DISPLAY TYPE
-----------------------------------------------------*/

typedef struct{
   MAIN_DISPLAY_TYPE main;
   MINI_DISPLAY_TYPE mini;
   string alpha;
   STATUS_TYPE status;
   DISPLAY_POSITION enhanced;
   LABELS_TYPE lab;
} DISPLAY_TYPE;
#define _cond_DISPLAY_TYPE(A,B,C) (A?B:C)
#define _assign_DISPLAY_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
WATCH_TIME_TYPE
-----------------------------------------------------*/
typedef struct {int day_in_week;
   int month;
   int day;
   int hours;
   int minutes;
   int seconds;
   int mode12h;
} WATCH_TIME_TYPE;
#define _cond_WATCH_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_WATCH_TIME_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
WATCH_TIME_POSITION
-----------------------------------------------------*/

typedef int WATCH_TIME_POSITION;
#define _cond_WATCH_TIME_POSITION(A,B,C) (A?B:C)
#define _assign_WATCH_TIME_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
ALARM_TIME_TYPE
-----------------------------------------------------*/

typedef struct {
   int hours;
   int minutes;
   int mode12h;
} ALARM_TIME_TYPE;
#define _cond_ALARM_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_ALARM_TIME_TYPE(X,Y) (*(X)=(Y))

/*----------------------------------------------------
ALARM_TIME_POSITION
-----------------------------------------------------*/

typedef int ALARM_TIME_POSITION;
#define _cond_ALARM_TIME_POSITION(A,B,C) (A?B:C)
#define _assign_ALARM_TIME_POSITION(X,Y) (*(X)=(Y))

/*----------------------------------------------------
STOPWATCH_TIME_TYPE
-----------------------------------------------------*/
typedef struct {
   int hours;
   int minutes;
   int seconds;
   int hsec;
} STOPWATCH_TIME_TYPE;
#define _cond_STOPWATCH_TIME_TYPE(A,B,C) (A?B:C)
#define _assign_STOPWATCH_TIME_TYPE(X,Y) (*(X)=(Y))

