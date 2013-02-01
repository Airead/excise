CC = gcc

CFLAGS	= -Wall -g
CFLAGS += -DUNIT_TESTING=1
#CFLAGS += $(shell pkg-config --cflags glib-2.0 )

LDFLAGS	= 
#LDFLAGS += $(shell pkg-config --libs glib-2.0)

INCLUDE = 
INCLUDE += -I../include

BIN = assert_module_test.out assert_macro_test.out customer_database_test.out \
	key_value_test.out calculator_test.out

%.o: %.c
	@echo CC -c $< -o $@
	@$(CC) -c $< $(CFLAGS) $(INCLUDE) -o $@ $(LDFLAGS)

%_test.out: %_test.o %.o cmockery/cmockery.o
	@echo CC $^ -o $@ 
	@$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean all test

all: $(BIN)

clean:
	rm -f *~ *.file *.out *.o $(BIN) core.* 

test:
	@echo BIN = $(BIN)
