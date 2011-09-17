CC	= gcc
CFLAGS	= -Wall -g -D_DEBUG_TRACE_
LDFLAGS	=

TARGETS	= select_test poll_test epoll_test

.PHONY: all clean

all: $(TARGETS)
	$(MAKE) -C unixdomain
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
	$(MAKE) -C unixdomain clean
