
gen :
	@lustre parity.lus verif_parity -v
	@ocmin verif_parity.oc -v
	@poc verif_parity_min.oc

genmin :
	@lustre parity.lus verif_parity -v -demand
	@poc verif_parity.oc

verif :
	@lesar parity.lus verif_parity -v

clean :
	/bin/rm -f *.ec *.oc *.c *.h *.bak
