CC	= gcc

CFLAGS	= -Wall -g
CFLAGS += $(shell pkg-config --cflags glib-2.0 )
CFLAGS += $(shell pkg-config --cflags dbus-glib-1)
#CFLAGS += $(shell pkg-config --cflags gtk+-2.0)

LDFLAGS	= 
LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += $(shell pkg-config --libs dbus-glib-1)
#LDFLAGS += $(shell pkg-config --libs gtk+-2.0)

SOURCE =  $(wildcard *.c)
TARGETS	:= $(patsubst %.c, %, $(SOURCE))
TARGETS := $(filter-out common_marshaler, $(TARGETS))

%: %.c
	@echo CC $< -o $@
	@$(CC) $< common_marshaler.c $(CFLAGS) -o $@ $(LDFLAGS)

.PHONY: all clean test marshaler

all: $(TARGETS) 

marshaler: common_marshaler.list
	glib-genmarshal --prefix _common_marshal --header common_marshaler.list > common_marshaler.h
	glib-genmarshal --prefix _common_marshal --body common_marshaler.list > common_marshaler.c

clean:
	rm -f *~ a.out *.o $(TARGETS) core.*

test:
	@echo TARGETS: $(TARGETS)


