CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	= -lpthread

TARGETS	= tcp_server tcp_multiprocess_server tcp_multithreads_server

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
