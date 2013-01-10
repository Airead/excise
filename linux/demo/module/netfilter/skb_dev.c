/**
 * @file skb_dev.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/06 16:34:19
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <net/netfilter/nf_conntrack.h>
#include <linux/netfilter/nf_conntrack_common.h>

/* function to be called by hook */
static unsigned int 
hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
          const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    if (!skb) {
        return NF_ACCEPT;
    }

    if (in == NULL) {
        return NF_ACCEPT;
    } else if (in->name == NULL) {
        return NF_ACCEPT;
    }

    pr_info("in->name: %s\n", in->name);

    return NF_ACCEPT;
}

static struct nf_hook_ops nfho = {
    .hook = hook_func,
    .hooknum = 	NF_INET_FORWARD,
    .pf = PF_INET,
    .priority = NF_IP_PRI_MANGLE,
};

static int __init my_init_module(void)
{
    int ret;

    ret = nf_register_hook(&nfho);         /* register hook */
    if (ret < 0) {
        goto failed;
    }

    return 0;                   /* return 0 for success */
   
failed:
    return ret;
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */

    printk("rmmod  module\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("skb_dev");
MODULE_LICENSE("GPL");
