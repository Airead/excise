CC	= $(CROSS_COMPILE)gcc
CFLAGS	= -Wall -g
LDFLAGS	= #-static

TARGETS	= chmod_test chown_test truncate_test link_test unlink_test \
	  remove_test print_args rename_test symlink_test readlink_test \
	  touch utime_test mkdir_test rmdir_test ls ls1 chdir_test

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f *.o *~ a.out $(TARGETS)
