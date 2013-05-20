CC = gcc

CFLAGS	= -Wall -g -std=gnu99

LDFLAGS	= 

INCLUDE = 

OBJS_RAW = $(shell ls *.c)
OBJS = $(patsubst %.c,%.o,$(OBJS_RAW))

%.o: %.c
#	@echo CC -c $< -o $@
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

%.out: %.o lcut.c
#	@echo CC $^ -o $@ 
	$(CC) $^ -o $@ $(LDFLAGS) $(INCLUDE)

.PHONY: clean all test

all: $(LIB) $(OBJS)

$(LIB):
#	make -C ../

clean:
	rm -f *~ *.file *.out *.o $(BIN) core.* 
test:
	@echo BIN = $(BIN)
	@echo OBJS = $(OBJS)

