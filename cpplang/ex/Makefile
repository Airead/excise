CC = g++
CPPFLAGS = -g -Wall
LDFLAGS = 

TARGET: 2.7.1.out 2.7.2.out 2.7.3.out 2.7.4.out 2.7.5.out 2.7.6.out 2.7.7.out \
	3.7.1.out 3.7.2.out 3.7.3.out 3.7.4.out \
	4.13.1.out 4.13.2.out 4.13.3.out 4.13.4.out 4.13.5.out 4.13.6.out 4.13.7.out 4.13.8.out 4.13.9.out

%.out: %.cc
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)

debug:
	@echo TARGET: $(TARGET)