CC = gcc

CFLAGS = -Wall -g


INCLUDE = $(shell pkg-config --cflags dbus-glib-1 \
				glib-2.0 \
			)
LDFLAGS = $(shell pkg-config --libs dbus-glib-1 \
	 			glib-2.0 \
			)	

SOURCE = sms-marshal.c

.PHONY: clean smsc

client: client.c $(SOURCE)
	gcc $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

server: server.c $(SOURCE)
	gcc $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

clean:
	rm -f client server *~ *# *.o
