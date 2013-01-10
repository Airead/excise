obj-m += skb_dev.o
obj-m += conntrack_state.o
KDIR = /lib/modules/$(shell uname -r)/build
MDIR = $(PWD)

all:
	make -C $(KDIR) M=$(MDIR) modules

clean:
	make -C $(KDIR) M=$(MDIR) clean
	rm -f poll