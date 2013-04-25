CC=gcc  

IPTABLES_SRC=/home/airead/downloads/tar/iptables-v1.4.12
INCLUDE=-I$(IPTABLES_SRC)/include  
KERNEL_SRC=/lib/modules/`uname -r`/build  
MOD=ipt_MYSNAT.ko  

obj-m = ipt_MYSNAT.o

all: modules libipt_MYSNAT.so  

modules: $(MOD)  

ipt_MYSNAT.ko:  ipt_MYSNAT.c  
	$(MAKE) -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules  

libipt_MYSNAT.so: libipt_MYSNAT.c  
	$(CC)  $(INCLUDE) -fPIC -c libipt_MYSNAT.c  
	ld -shared -o libipt_MYSNAT.so libipt_MYSNAT.o  

clean:  
	-rm -f *.o *.so *.ko .*.cmd *.mod.c *.symvers *.order  

install: all  
	cp -rf libipt_MYSNAT.so /lib/xtables/  
	cp -rf $(MOD) /lib/modules/`uname -r`/kernel/net/ipv4/netfilter/  