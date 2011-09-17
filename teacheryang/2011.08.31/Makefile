CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= test1 daemon_test test2 kill_test raise_test abort_test \
	  sigpipe_test alarm_test alarm_pause block_signals

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
