CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= dup redirect test1 test2 test3 fb_test test4 \
	  stat test5 access \
	  lstat

.PHONY: all clean

all: $(TARGETS)
	$(MAKE) -C shm

clean:
	rm -f *.o *~ a.out $(TARGETS)
	$(MAKE) -C shm clean
