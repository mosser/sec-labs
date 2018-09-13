
/*
The main program for watch simulation under UNIX

Files to include
*/

typedef char* string;
#include <curses.h>
/*
#include <sgtty.h>
*/

#include <signal.h>
#include <setjmp.h>
#include <sys/time.h>
#include "MAIN.h"
#include "WATCH.h"



/*
Extern declarations
*/

extern void DISPLAY_INIT () ;

extern bye();

extern WATCH_TIME_TYPE INITIAL_WATCH_TIME;

extern WATCH_TIME_TYPE GET_INITIAL_WATCH_TIME();

int pipenos[2];


/*
The main program

We first initialize the screen and get the current time.
We then open the pipe between the master and slave process and fork.
The master process multiplexes the four keyboard keys and the time
into the pipe. The slave process calls the WATCH program
*/

jmp_buf env;
int pid;

char ul, ur, ll, lr;

main (argc,argv)
int argc;
char ** argv; {

   DISPLAY_INIT ();
   INITIAL_WATCH_TIME = GET_INITIAL_WATCH_TIME ();

   /* get input keys */
   switch (argc) {
      case 1 : ul='4'; ur='5'; ll='1'; lr='2'; break;
      case 2 : 
               if (strlen(argv[1])==4) {
                  ul=argv[1][0];
                  ur=argv[1][1];
                  ll=argv[1][2];
                  lr=argv[1][3];
                  break;
	       }
      default : fprintf (stderr, "Usage :\nww : ul=4, ur=5, ll=1, lr=2 for\
 numeric pad\nww abcd : ul=a, ur=b, ll=c, lr=d for any keys abcd\n");
                exit(1);
   }
   pipe(pipenos);

   switch (pid=fork()) {
      case -1 : fprintf(stderr, "Unable to fork\n");
                exit(0);
                break;
      case 0 : slave();
               break;
      default : master();
                break;
   }
}

/*
Master process : keyboard and time multiplexing
*/

void sigalrm (int i) {
   write(pipenos[1],"h",1);
   signal(SIGALRM,sigalrm);
   longjmp(env,1);
}

master () {
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


slave () {
char buffer[4];
	New_Watch_reset();
	for(;;){
		read(pipenos[0],buffer,1);
        	New_Watch_I_time_unit(0); New_Watch_I_LL(0); New_Watch_I_LR(0); New_Watch_I_UL(0); New_Watch_I_UR(0);
		switch (buffer[0]) {
        	case 'h' : New_Watch_I_time_unit(1); break;
			case '1' : New_Watch_I_LL(1); break;
			case '2' : New_Watch_I_LR(1); break;
			case '4' : New_Watch_I_UL(1); break;
			case '5' : New_Watch_I_UR(1); break;
			default: break;
		}
	    New_Watch();
	}
}

