/*

tcl_init_lustre.h
------------------
Distrib III

A tcl/tk installation is no longer distributed with lustre:
lustre tools are built according to the tcl stubs mechanism
and then rely on a existing tcl/tk instalation on the host machine.

However some init must still be done:

- declare "absolutepath"
- recherche LUSTRE_INSTALL/tcl and init les variables :
  . tcl_libPath
  . lustre_install

- Invocation of Tcl_InitLustre must appear BEFORE
  tcl/tk init :

	if(!tcl_interpret){
		return TCL_ERROR;
	}
	if(Tcl_InitLustre(tcl_interpret) != TCL_OK){
		return TCL_ERROR;
	}
	if (Tcl_Init(tcl_interpret) != TCL_OK){
		return TCL_ERROR;
	} 
	if (Tk_Init(tcl_interpret) != TCL_OK){
		return TCL_ERROR;
	} 
*/

int Tcl_InitLustre(Tcl_Interp* tcl_interpret);

/*----------------------------------------------------------------
File : tcl_timer.h
Goal : tcl interpreter customizations
------------------------------------------------------------------
Usage :
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <tcl.h>
#include <tk.h>
------------------------------------------------------------------
Procedure :

   int TimeHandler_Init(Tcl_Interp* tcl_interpret)

Input : the tcl interpret to customize, which must be already
        tcl-initialized
Output : TCL_OK or TCL_ERROR
------------------------------------------------------------------
Description :
	Add a timer handler command to a tcl interpret 
	The command is :
		add_timer <milliseconds> <command-line>
	where <milliseconds> is a positive integer
	and <command-line> a tcl script
	the return value is a timer-token that can be used in :
		abort_timer <timer-handler>
----------------------------------------------------------------*/
extern int TimeHandler_Init(Tcl_Interp* tcl_interpret);
