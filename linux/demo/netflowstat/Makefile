CC	= gcc

CFLAGS	= -Wall -g
#CFLAGS += $(shell pkg-config --cflags netfilter_queue)
#CFLAGS += -D_DEBUG_

LDFLAGS	= 
LDFLAGS += 

all:

TARGETS = netflows netflowc

netflowc: netflowc.c
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

netflows: netflows.c
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

.PHONY: all clean test

all: $(TARGETS)

clean:
	rm -f *~ a.out *.o $(TARGETS) $(OBJECT) core.*

test:
	@echo TARGETS: $(TARGETS)


