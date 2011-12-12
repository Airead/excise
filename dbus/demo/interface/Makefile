CC = gcc

CFLAGS = -Wall -g


INCLUDE = $(shell pkg-config --cflags dbus-glib-1 \
				glib-2.0 \
			)
LDFLAGS = $(shell pkg-config --libs dbus-glib-1 \
	 			glib-2.0 \
			)	

BIN = smss
SOURCE = gsm_sms.c sms_features.c sms-marshal.c

smss: smss.c $(SOURCE)
	gcc $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

.PHONY: clean smsc

smsc: smsc.c $(SOURCE)
	gcc $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

clean:
	rm -f smss smsc *~ *# *.o
