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
TARGETS_OUT = common_marshaler basic_data
TARGETS := $(filter-out $(TARGETS_OUT), $(TARGETS))

%: %.c
	@echo CC $< -o $@
	@$(CC) $< common_marshaler.c basic_data.c $(CFLAGS) -o $@ $(LDFLAGS)

.PHONY: all clean test marshaler

all: $(TARGETS) 

marshaler: 
	glib-genmarshal --prefix _common_marshal --header common_marshaler.list > common_marshaler.h
	glib-genmarshal --prefix _common_marshal --body common_marshaler.list > common_marshaler.c
	dbus-binding-tool --prefix=airead_fan --mode=glib-server all_basic_data_deliver_server.xml > all_basic_data_deliver_server.h

clean:
	rm -f *~ a.out *.o $(TARGETS) core.*

test:
	@echo TARGETS: $(TARGETS)


