CC = gcc

CFLAGS	= -Wall -g
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )

LDFLAGS	= 
# LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += -llcut

INCLUDE = 
INCLUDE += -I../include

BIN = justrun.out string_test.out mock_test.out calculator_test.out

calculator_test.out: calculator_test.o calculator.o
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

%.out: %.o
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean all test

all: $(BIN)

clean:
	rm -f *~ *.file *.out *.o $(BIN) $(EBIN) core.* 

test:
	@echo BIN = $(BIN)
