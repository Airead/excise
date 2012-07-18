#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/netdevice.h>

#define VERSION 	"0.00"
 
static struct notifier_block pktgen_notifier_block = {
	.notifier_call = NULL, //pktgen_device_event,
};

static int __init fpg_init(void)
{
	printk(KERN_INFO "start initilaize fun package gen\n");

    /* Register us to receive netdevice events */
	register_netdevice_notifier(&pktgen_notifier_block);

	return 0;
}
 
static void __exit fpg_cleanup(void)
{
	printk(KERN_INFO "cleanup fun package gen\n");
}

module_init(fpg_init); 
module_exit(fpg_cleanup);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("Packet Generator tool");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
