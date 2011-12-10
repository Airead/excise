CC = gcc

CFLAGS = -Wall -g


INCLUDE = $(shell pkg-config --cflags dbus-glib-1 \
				glib-2.0 \
			)
LDFLAGS = $(shell pkg-config --libs dbus-glib-1 \
	 			glib-2.0 \
			)	

BIN = smss
OBJECT = smss.o gsm_sms.o sms_features.o 

%.o: %.c
	gcc $(CFLAGS) $(INCLUDE) $< -o $@ $(LDFLAGS)

$(BIN): $(OBJECT)
	gcc $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(BIN) *~ *# *.o
