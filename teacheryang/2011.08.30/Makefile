CC	= gcc
CFLAGS	= -Wall -g
LDFLAGS	=

TARGETS	= execve_test print_args print_env \
	  test1 \
	  print_ids execute_setuid \
	  setuid_test test2 \
	  system_test \
	  setpgid_test setpgid_test2 setpgid_test3 \
	  setsid_test

.PHONY: all clean

all: $(TARGETS)
	
clean:
	rm -f *~ a.out *.o $(TARGETS) core.*
