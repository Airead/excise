CC = g++
CPPFLAGS = -g -Wall
LDFLAGS = 

TARGET: 2.7.1.out 2.7.2.out 2.7.3.out 2.7.4.out 2.7.5.out 2.7.6.out 2.7.7.out \
	3.7.1.out 3.7.2.out

%.out: %.cc
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)

debug:
	@echo TARGET: $(TARGET)