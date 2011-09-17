CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	= -lpthread

TARGETS	= 

.PHONY: all clean

all: $(TARGETS)
	$(MAKE) -C tcp
	$(MAKE) -C udp
	$(MAKE) -C tftp
	$(MAKE) -C dns
	$(MAKE) -C broadcast
	$(MAKE) -C multicast
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
	$(MAKE) -C tcp clean
	$(MAKE) -C udp clean
	$(MAKE) -C tftp clean
	$(MAKE) -C dns clean
	$(MAKE) -C broadcast clean
	$(MAKE) -C multicast clean
