obj-m += genpkt.o
obj-m += genpkt_ex.o
KDIR = /lib/modules/$(shell uname -r)/build
MDIR = $(PWD)

all:
	make -C $(KDIR) M=$(MDIR) modules

clean:
	make -C $(KDIR) M=$(MDIR) clean
