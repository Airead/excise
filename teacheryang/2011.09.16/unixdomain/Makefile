CC	= gcc
CFLAGS	= -Wall -g -D_DEBUG_TRACE_
LDFLAGS	=

TARGETS	= 

.PHONY: all clean

all: $(TARGETS)
	$(MAKE) -C stream
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
	$(MAKE) -C stream clean
