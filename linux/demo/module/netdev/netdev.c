/**
 * @file fs.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/20 16:02:43
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/netdevice.h>

#define PMAC(mac) \
    pr_info("   '-->%02x:%02x:%02x:%02x:%02x:%02x\n",                          \
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5])

static int netdev_init_module(void)
{
    struct net_device *dev;

    read_lock(&dev_base_lock);
    for_each_netdev(&init_net, dev) {
        pr_info("dev_name: %s\n", dev->name);
        PMAC(dev->dev_addr);
    }
    read_unlock(&dev_base_lock);
    
    return 0;
}

static void netdev_cleanup_module(void)
{
    return;
}


module_init(netdev_init_module);
module_exit(netdev_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("net_device view");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.00");

