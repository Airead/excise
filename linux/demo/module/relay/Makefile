obj-m += relay.o
KDIR = /lib/modules/$(shell uname -r)/build
MDIR = $(PWD)

all:
	make -C $(KDIR) M=$(MDIR) modules
	gcc -g poll.c -o poll

clean:
	make -C $(KDIR) M=$(MDIR) clean
	rm -f poll