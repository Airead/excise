CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	= -lrt

TARGETS	= create send receive unlink getattr

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
