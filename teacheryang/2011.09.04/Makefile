CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= pipe_test mkfifo_test write_fifo read_fifo

.PHONY: all clean

all: $(TARGETS)
	$(MAKE) -C mq
	$(MAKE) -C semaphore
	$(MAKE) -C shm
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
	$(MAKE) -C mq clean
	$(MAKE) -C semaphore clean
	$(MAKE) -C shm clean
