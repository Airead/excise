CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= signal_test sigaction_test test1 test2 sigqueue_test test3 \
	  print_signal_state test4 alarm_sigsuspend sigchld_test

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
