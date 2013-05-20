CC = gcc

CFLAGS	= -Wall -g -std=gnu99
#CFLAGS += -D_DEBUG_COLOR
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )

LDFLAGS	= 
#LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += -lm

INCLUDE = 
INCLUDE += -I../

MAIN = bintree.main
BIN = test_bintree.out
#LIB = ../src/libair.a

%.o: %.c
#	@echo CC -c $< -o $@
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

test_%.out: ../%.o test_%.o lcut.c
#	@echo CC $^ -o $@ 
	$(CC) $^ -o $@ $(LDFLAGS) $(INCLUDE)

%.main: ../%.o %_main.o
	$(CC) $^ -o $@ $(LDFLAGS) $(INCLUDE)

.PHONY: clean all test

all: $(LIB) $(BIN) $(MAIN)

$(LIB):
	make -C ../

clean:
	rm -f *~ *.file *.main *.out *.o $(BIN) core.*
test:
	@echo BIN = $(BIN)
