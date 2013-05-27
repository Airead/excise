CC = g++

LIBS = `pkg-config --libs GraphicsMagick++`
CFLAGS = `pkg-config --cflags GraphicsMagick++`

BIN = crop.out zoom.out draw.out grayscale.out grayscale2.out strip.out

%.out: %.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

all: $(BIN)

clean:
	rm -rf $(BIN) *.o *~

test:
	@echo LIBS = $(LIBS)
	@echo CFLAGS = $(CFLAGS)