CC = gcc

CFLAGS = -g -Wall

BIN = hello_http_parser.out parse_request.out parse_response.out

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.out: %.o http_parser.o
	$(CC) $(CLFAGS) $^ -o $@

.PHONY: all clean test
all: $(BIN)

clean:
	rm -rf *~ *.o *.out $(BIN)