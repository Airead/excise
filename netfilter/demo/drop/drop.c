/**
 * @file drop.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/05 15:27:30
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nfho; /* struct holding set of hook function optionsj */

/* function to be called by hook */
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    printk(KERN_INFO "packet dropped\n"); /* log to /var/log/messages */
    return NF_DROP;                        /* dorps the packet */
}

int __init init_module()
{
    nfho.hook = hook_func;      /* function to call when conditions below met */
    nfho.hooknum = NF_INET_PRE_ROUTING; /* called right after packet recieved, first hook in Netfilter */
    nfho.pf = PF_INET;                /* IPV4 packets */
    nfho.priority = NF_IP_PRI_FIRST; /* set to highest priority over all other hook functions */
    nf_register_hook(&nfho);         /* register hook */

    return 0;                   /* return 0 for success */
}

/* Call when module unloaded using 'rmmod' */
void __exit cleanup_module()
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */
}

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("drop all packets");
MODULE_LICENSE("GPL");
MODULE_ALIAS("drop_all_packets");

