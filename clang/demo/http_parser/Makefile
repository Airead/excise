CC = gcc

CFLAGS = -g -Wall -DHTTP_PARSER_STRICT=1

BIN = hello_http_parser.out

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.out: %.o http_parser.o
	$(CC) $(CLFAGS) $^ -o $@

.PHONY: all clean test
all: $(BIN)

clean:
	rm -rf *~ *.o *.out $(BIN)