
simul :
	@luciole minus.lus minus

gen :
	@lustre minus.lus minus -v
	@ocmin minus.oc -v
	@poc minus_min.oc

genmin :
	@lustre minus.lus minus -v -demand
	@poc minus.oc

verif :
	@lesar minus.lus minus -diag -v

clean :
	/bin/rm -f *.ec *.oc *.c *.h *.bak 
