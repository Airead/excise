CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= exit_test atexit_test getopt_test \
	  print_env getenv_test putenv_test setenv_test \
	  test1 \
	  print_ids fork_test vfork_test \
	  wait_test waitpid_test

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
