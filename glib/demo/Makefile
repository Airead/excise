CC	= gcc

CFLAGS	= -Wall -g
CFLAGS += $(shell pkg-config --cflags glib-2.0 )
CFLAGS += $(shell pkg-config --cflags gio-2.0 )
#CFLAGS += $(shell pkg-config --cflags dbus-glib-1)
#CFLAGS += $(shell pkg-config --cflags gtk+-2.0)

LDFLAGS	= 
LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += $(shell pkg-config --libs gio-2.0)
#LDFLAGS += $(shell pkg-config --libs dbus-glib-1)
#LDFLAGS += $(shell pkg-config --libs gtk+-2.0)

SOURCE =  $(wildcard *.c)
TARGETS	:= $(patsubst %.c, %, $(SOURCE))

%: %.c
	@echo $(CC) $< -o $@
	@$(CC) $< $(CFLAGS) -o $@ $(LDFLAGS)

.PHONY: all clean test

all: $(TARGETS)

clean:
	rm -f *~ a.out *.o $(TARGETS) core.*

test:
	@echo TARGETS: $(TARGETS)


