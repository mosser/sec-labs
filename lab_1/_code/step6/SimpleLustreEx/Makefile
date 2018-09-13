FILE=edge2.lus
NODE=obs
OUTPUTNAME=`basename $(FILE) .lus`_$(NODE)

all:  demo

#for interactive stdin/stdout output
demostd: $(FILE)
	lus2c $(FILE) $(NODE) -loop
	gcc -o $(OUTPUTNAME) $(NODE).c $(NODE)_loop.c 

#for luciole test.
demo: $(FILE)
	luciole $(FILE) $(NODE)

#compile to automata
auto: $(FILE)
	lus2atg $(FILE) $(NODE)

#call the model checker (works if there is an observer)
check : $(FILE)
	lesar $(FILE) $(NODE) -v 

#if you want to check a formula directly you can also use xlesar

clean:
	rm -f *.o *~ *.oc *.ec $(NODE).c $(NODE).h *_loop.c $(OUTPUTNAME) *.atg
