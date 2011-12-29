CC	= gcc

CFLAGS	= -Wall -g
CFLAGS += -D_DEBUG_
CFLAGS += $(shell pkg-config --cflags glib-2.0 )
CFLAGS += $(shell pkg-config --cflags dbus-glib-1)
CFLAGS += $(shell pkg-config --cflags gio-2.0)

LDFLAGS	= 
LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += $(shell pkg-config --libs dbus-glib-1)
LDFLAGS += $(shell pkg-config --libs gio-2.0)

BIN = main
SOURCE =  $(wildcard *.c)
OBJECT	= $(patsubst %.c, %.o, $(SOURCE))

%.o: %.c
	@$(CC) -c $< $(CFLAGS) -o $@ $(LDFLAGS)

$(BIN): $(OBJECT)
	@$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

.PHONY: all clean test

all: $(OBJECT)

clean:
	rm -f *~ a.out *.o $(TARGETS) core.* \
		$(BIN)

test:
	@echo TARGETS: $(TARGETS)
	@echo OBJECTS: $(OBJECTS)


