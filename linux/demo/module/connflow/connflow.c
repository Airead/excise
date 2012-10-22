/**
 * @file connflow.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/16 10:20:23
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/ctype.h>
#include <linux/netdevice.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/route.h>
#include <net/dst.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_REJECT.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_extend.h>
#include <net/netfilter/nf_conntrack_acct.h>

/*
 * Macros to help debugging
 */

#define CONNFLOW_DEBUG

#undef PDEBUG             /* undef it, just in case */
#ifdef CONNFLOW_DEBUG
#  ifdef __KERNEL__
/* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_INFO "connflow: " fmt, ## args)
#  else
/* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#define VERSION 	"0.00"

#define ADDR_BUFF_SIZE (sizeof("xxx.xxx.xxx.xxx:xxxxx"))
#define DATA_SIZE 1024
#define BUF_SIZE 4096

static char *devname = "all";
static struct iphdr *iph;        /* ip header struct */
//static struct tcphdr *tcph;      /* tcp header struct */

/* function to be called by hook */
static unsigned int 
hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
          const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
    struct nf_conn_counter *acct;

    if (!skb) {
        return NF_ACCEPT;
    }

    if (in == NULL) {
        return NF_ACCEPT;
    } else if (in->name == NULL) {
        return NF_ACCEPT;
    }
    
    if (memcmp(devname, "all", 3) != 0) {
        if (memcmp(devname, in->name, 4) != 0) {
            return NF_ACCEPT;
        }
    }

    /* conntrack check */
    if (skb->nfct == NULL) {
        /* if (net_ratelimit())
         *     pr_info("skb->nfct == NULL!\n"); */
        return NF_ACCEPT;
    }
    ct = nf_ct_get(skb, &ctinfo);

    acct = nf_conn_acct_find(ct);
    if (!acct) {
        if (net_ratelimit())
            pr_info("acct is NULL\n");
        return NF_ACCEPT;
    }

	if (ct->proto.tcp.state == TCP_CONNTRACK_CLOSE_WAIT) {
        pr_info("%pI4 --> %pI4: %llu bytes CLOSE_WAIT\n", &iph->saddr, &iph->daddr, 
            acct[IP_CT_DIR_ORIGINAL].bytes + acct[IP_CT_DIR_REPLY].bytes);
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops nfho = {
    .hook = hook_func,
    .hooknum = 	NF_INET_PRE_ROUTING,
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

    printk("insmod connflow module, dev: %s\n", devname);

    return 0;                   /* return 0 for success */
   
failed:
    return ret;
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */
    printk("rmmod connflow module\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("connflow");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
