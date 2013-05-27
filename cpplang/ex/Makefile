CC = g++
CPPFLAGS = -g -Wall -std=c++0x
LDFLAGS = 

TARGET := 2.7.1.out 2.7.2.out 2.7.3.out 2.7.4.out 2.7.5.out 2.7.6.out 2.7.7.out \
	3.7.1.out 3.7.2.out 3.7.3.out 3.7.4.out \
	4.13.1.out 4.13.2.out 4.13.3.out 4.13.4.out 4.13.5.out 4.13.6.out 4.13.7.out 4.13.8.out 4.13.9.out \
	5.9.1.out 5.9.3.out 5.9.4.out 5.9.5.out 5.9.6.out 5.9.7.out 5.9.8.out 5.9.9.out 5.9.10.out \
	6.11.1.out 6.11.2.out 6.11.3.out 6.11.8.out \
	7.13.1.out 7.13.2.out 7.13.3.out 7.13.5.out 7.13.6.out 7.13.7.out list7.15.out 7.13.8.a.out 7.13.8.b.out 7.13.10.out \
	8.8.1.out 8.8.2.out 8.8.3.out 8.8.4.out 8.8.5.out 8.8.6.out list8.14.out 8.8.7.out \
	9.6.1.out list9.9.out 9.6.2.out

%.out: %.cc
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

9.6.1.out: 9.6.1.cc golf.cc
	$(CC) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(TARGET)

debug:
	@echo TARGET: $(TARGET)