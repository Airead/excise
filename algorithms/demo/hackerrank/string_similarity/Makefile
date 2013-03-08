CC = gcc
CFLAGS = -g -Wall
LDFLAGS = 

BIN = code1.out
DEBUG_BIN = code1.debug

%.debug: %.c
	$(CC) $(CFLAGS) -D_DEBUG $^ -o $@ $(LDFLAGS)

%.out: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: all clean debug

all: $(BIN) $(DEBUG_BIN)

clean:
	rm -rf $(BIN)

debug:
	@echo "BIN = $(BIN)"
	@echo "DEBUG_BIN = $(DEBUG_BIN)"