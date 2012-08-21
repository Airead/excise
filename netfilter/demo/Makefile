CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lnfnetlink -lnetfilter_queue

TARGETS := pkt_print

all: $(TARGETS)

pkt_print: pkt_print.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *~ a.out *.o $(TARGETS) core.*

test:
	@echo TARGETS: $(TARGETS)
