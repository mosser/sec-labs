
/*
The main program for watch simulation under UNIX
*/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include <unistd.h>
#include "New_Watch.h"
#include "New_Watch_ext.h"

extern void DISPLAY_INIT () ;
extern void DISPLAY_END () ;

void bye() {
   DISPLAY_END();
   exit(0);
}

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
Global variables
*/
static int pipenos[2];
static jmp_buf env;
static int pid;
static char ul, ur, ll, lr;

void master();
void slave();

int main (int argc, char* argv[])
{
   /* get input keys */
   switch (argc) {
      case 1 :
         ul='4'; ur='5'; ll='1'; lr='2'; break;
      case 2 :
         if (strlen(argv[1])==4) {
            ul=argv[1][0];
            ur=argv[1][1];
            ll=argv[1][2];
            lr=argv[1][3];
            break;
         }
      default :
         fprintf (stderr, "Usage :\n");
         fprintf (stderr, "%s : ul=4, ur=5, ll=1, lr=2 for numeric pad\n", argv[0]);
         fprintf (stderr, "%s abcd : ul=a, ur=b, ll=c, lr=d for any keys abcd\n", argv[0]);
         exit(1);
   }
   DISPLAY_INIT ();
   INITIAL_WATCH_TIME = GET_INITIAL_WATCH_TIME ();
   pipe(pipenos);
   switch (pid=fork()) {
      case -1 :
         fprintf(stderr, "Unable to fork\n");
         exit(0);
      break;
      case 0 :
         slave();
      break;
      default :
         master();
      break;
   }
	return 0;
}

/*
Master process : keyboard and time multiplexing
*/

void sigalrm (int i) {
   write(pipenos[1],"h",1);
   signal(SIGALRM,sigalrm);
   longjmp(env,1);
}

void master () {
   char c;
   static struct itimerval value, ovalue;

   signal(SIGALRM,sigalrm);
   getitimer(0, &ovalue);
   value = ovalue;
   value.it_value.tv_usec = 100000;
   value.it_interval.tv_usec = 100000;
   setitimer(ITIMER_REAL, &value, &ovalue);

   for (;;) {
      setjmp(env);
      c=getchar();
      if (c==ul) write(pipenos[1],"4",1);
      if (c==ur) write(pipenos[1],"5",1);
      if (c==ll) write(pipenos[1],"1",1);
      if (c==lr) write(pipenos[1],"2",1);
      if (c=='q' || c=='Q') {
         setitimer(ITIMER_REAL, &ovalue, &value);
         kill(pid,SIGKILL);
         bye();
      }
   }
}

/*
Slave process
*/

void slave () {
char buffer[4];
   /* Context allocation */
   struct New_Watch_ctx* ctx = New_Watch_new_ctx(NULL);
 
   for(;;){
      read(pipenos[0],buffer,1);
      New_Watch_I_time_unit(ctx, 0);
      New_Watch_I_LL(ctx, 0);
      New_Watch_I_LR(ctx, 0);
      New_Watch_I_UL(ctx, 0);
      New_Watch_I_UR(ctx, 0);
      switch (buffer[0]) {
         case 'h' : New_Watch_I_time_unit(ctx, 1); break;
         case '1' : New_Watch_I_LL(ctx, 1); break;
         case '2' : New_Watch_I_LR(ctx, 1); break;
         case '4' : New_Watch_I_UL(ctx, 1); break;
         case '5' : New_Watch_I_UR(ctx, 1); break;
         default: break;
      }
      New_Watch_step(ctx);
   }
}

