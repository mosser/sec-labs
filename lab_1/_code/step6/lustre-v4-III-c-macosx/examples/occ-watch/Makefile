LSRC = LUSTRE_SRC
CSRC = C_SRC
OBJDIR = OBJ

EC2OC = ec2oc -v -demand -oc5
CC = gcc
#CC = cc
OCC = occ -B New_Watch -D $(OBJDIR)
CFLAGS = -c -g -I$(CSRC)

OBJS = $(OBJDIR)/watch.o \
	$(OBJDIR)/stopwatch.o \
	$(OBJDIR)/alarm.o \
	$(OBJDIR)/display.o \
	$(OBJDIR)/console.o \
	$(OBJDIR)/watchmain.o \
	$(OBJDIR)/beep.o 

TESTOBJS = $(OBJDIR)/watch.o \
	$(OBJDIR)/stopwatch.o \
	$(OBJDIR)/alarm.o \
	$(OBJDIR)/display.o \
	$(OBJDIR)/console.o \
	$(OBJDIR)/watchtest.o \
	$(OBJDIR)/beep.o 

all : watch

test : watchtest

watch : $(OBJDIR)/New_Watch.o $(OBJS)
	$(CC) $(OBJS) $(OBJDIR)/New_Watch.o -O -lcurses -ltermcap -o watch

watchtest : $(OBJDIR)/New_Watch.o $(TESTOBJS)
	$(CC) $(TESTOBJS) $(OBJDIR)/New_Watch.o -O -lcurses -ltermcap -o watchtest

$(OBJDIR)/watchtest.o: $(CSRC)/MAIN.h $(CSRC)/watchtest.c $(CSRC)/WATCH.h
	$(CC) $(CFLAGS) $(CSRC)/watchtest.c -o $(OBJDIR)/watchtest.o


$(OBJDIR)/New_Watch.oc : $(LSRC)/New_Watch.lus
	lus2ec $(LSRC)/New_Watch.lus New_Watch -o $(OBJDIR)/New_Watch.ec
	$(EC2OC) $(OBJDIR)/New_Watch.ec -o $(OBJDIR)/New_Watch.oc

$(OBJDIR)/New_Watch.c : $(OBJDIR)/New_Watch.oc
	$(OCC) $(OBJDIR)/New_Watch.oc

$(OBJDIR)/New_Watch.o : $(OBJDIR)/New_Watch.c
	$(CC) $(CFLAGS) $(OBJDIR)/New_Watch.c -o $(OBJDIR)/New_Watch.o

$(OBJDIR)/watch.o : $(CSRC)/watch.c $(CSRC)/WATCH.h $(CSRC)/MAIN.h
	$(CC) $(CFLAGS) $(CSRC)/watch.c -o $(OBJDIR)/watch.o
	
$(OBJDIR)/stopwatch.o: $(CSRC)/stopwatch.c $(CSRC)/STOPWATCH.h $(CSRC)/MAIN.h
	$(CC) $(CFLAGS) $(CSRC)/stopwatch.c -o $(OBJDIR)/stopwatch.o

$(OBJDIR)/alarm.o: $(CSRC)/alarm.c $(CSRC)/ALARM.h \
					$(CSRC)/MAIN.h $(CSRC)/WATCH.h
	$(CC) $(CFLAGS) $(CSRC)/alarm.c -o $(OBJDIR)/alarm.o

$(OBJDIR)/display.o:  $(CSRC)/display.c  $(CSRC)/DISPLAY.h  \
					$(CSRC)/MAIN.h $(CSRC)/WATCH.h  \
					$(CSRC)/ALARM.h  $(CSRC)/STOPWATCH.h
	$(CC) $(CFLAGS) $(CSRC)/display.c -o $(OBJDIR)/display.o

$(OBJDIR)/console.o: $(CSRC)/console.c $(CSRC)/CONSOLE.h $(CSRC)/DISPLAY.h
	$(CC) $(CFLAGS) $(CSRC)/console.c -o $(OBJDIR)/console.o

$(OBJDIR)/watchmain.o: $(CSRC)/MAIN.h $(CSRC)/watchmain.c $(CSRC)/WATCH.h
	$(CC) $(CFLAGS) $(CSRC)/watchmain.c -o $(OBJDIR)/watchmain.o

$(OBJDIR)/beep.o: $(CSRC)/beep.c $(CSRC)/BEEP.h $(CSRC)/WATCH.h \
					$(CSRC)/STOPWATCH.h
	$(CC) $(CFLAGS) $(CSRC)/beep.c -o $(OBJDIR)/beep.o

clean :
	/bin/rm -f $(OBJDIR)/*
