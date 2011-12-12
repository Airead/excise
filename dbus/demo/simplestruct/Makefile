CC	= gcc

CFLAGS	= -Wall -g
CFLAGS += $(shell pkg-config --cflags glib-2.0 )
CFLAGS += $(shell pkg-config --cflags dbus-glib-1)

LDFLAGS	= 
LDFLAGS += $(shell pkg-config --libs glib-2.0)
LDFLAGS += $(shell pkg-config --libs dbus-glib-1)

SOURCE = 

sr_stream_server.h: sr_stream.xml
	dbus-binding-tool --prefix=webpad --mode=glib-server sr_stream.xml > sr_stream_server.h

.PHONY: all clean test server

server: server.c webpad.c
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

client: client.c
	$(CC) $^ $(CFLAGS) -o $@ $(LDFLAGS)

clean:
	rm -f *~ a.out *.o client server core.*

test:
	@echo TARGETS: $(TARGETS)


