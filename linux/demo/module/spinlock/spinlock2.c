/**
 * @file ipfrq.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/22 14:06:37
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>
#include <linux/slab.h>
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
#include <linux/hash.h>

/*
 * Macros to help debugging
 */

//#define IPFRQ_DEBUG
//#define TCP_HTTP

#undef PDEBUG             /* undef it, just in case */
#ifdef IPFRQ_DEBUG
#  ifdef __KERNEL__
/* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_INFO "ipfrq: " fmt, ## args)
#  else
/* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#define VERSION 	"0.00"

#define DATA_SIZE 1024
#define IPHASHNUM 8000

struct ipstat {
    __be32 destip;
    u32 count;
    time_t keepalive;
    time_t stage;               /* The identity of the used time period */
    struct hlist_node hash;
    struct rcu_head rcu_head;
};

static char *devname = "all";
static unsigned long duration = 10;
static unsigned long keepalive = 0;
static unsigned long clearcycle = 10;
static struct iphdr *iph;        /* ip header struct */
static struct tcphdr *tcph;      /* tcp header struct */
static int node_count;
static struct hlist_head ipstat_hash[IPHASHNUM];
static spinlock_t ipstat_hash_lock;
static struct kmem_cache *ipstat_cachep = NULL;

#define ipstat_hashfn(destip)	(hash_long(destip, 0) % IPHASHNUM)

struct ipstat *ipstat_create(__be32 destip)
{
    struct ipstat *tmp;

    tmp = kmem_cache_alloc(ipstat_cachep, GFP_KERNEL);
    if (tmp == NULL) {
        printk(KERN_WARNING "malloc failed: no memortn\n");
        return NULL;
    }
    memset(tmp, 0, sizeof(struct ipstat));

    return tmp;
}

static inline void ipstat_free(struct ipstat *ips) {
    kmem_cache_free(ipstat_cachep, ips);
}

/* function to be called by hook */
static unsigned int 
hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
          const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    struct ipstat *ips;
    u32 h;

    if (!skb) {
        return NF_ACCEPT;
    }
    
    if (iph->protocol != 6) {       /* not tcp, pass */
        return NF_ACCEPT;
    }

    /* get header size */
    tcph = (void *)skb->data + iph->ihl * 4;

    h = ipstat_hashfn(iph->daddr);
    
    if (node_count > 8000) {
        goto out;
    }
    ips = ipstat_create(iph->daddr);
    if (ips == NULL) {
        printk(KERN_WARNING "ipstat_create faild, no memory!\n");
        goto out;
    }
    node_count++;
    /* spin_lock_irq(&ipstat_hash_lock);
     * hlist_add_head_rcu(&ips->hash, &ipstat_hash[h]);
     * spin_unlock_irq(&ipstat_hash_lock); */
    ipstat_free(ips);
out:
    return NF_ACCEPT;
}

static struct nf_hook_ops nfho = {
    .hook = hook_func,
    .hooknum = 	NF_INET_PRE_ROUTING,
    .pf = PF_INET,
    .priority = NF_IP_PRI_MANGLE,
};

static void ipstat_hash_init(void)
{
    int i;

    for (i = 0; i < IPHASHNUM; i++) {
        INIT_HLIST_HEAD(&ipstat_hash[i]);
    }
}

static void ipstat_hash_free(void)
{
    int i;
    struct ipstat *ips;
    struct hlist_node *entry, *ntmp;
    struct timeval tv;

    do_gettimeofday(&tv);
    for (i = 0; i < IPHASHNUM; i++) {
        hlist_for_each_entry_safe(ips, entry, ntmp, &ipstat_hash[i], hash) {
            hlist_del(&ips->hash);
            ipstat_free(ips);
            node_count--;
        }
        INIT_HLIST_HEAD(&ipstat_hash[i]);
    }
}

static int __init my_init_module(void)
{
    int ret;

    ipstat_hash_init();
    spin_lock_init(&ipstat_hash_lock);

    ipstat_cachep = KMEM_CACHE(ipstat, SLAB_HWCACHE_ALIGN);
    if (ipstat_cachep == NULL) {
        pr_info("ipstat create kmem_cache failed\n");
        goto failed;
    }
    
    ret = nf_register_hook(&nfho);         /* register hook */
    if (ret < 0) {
        goto failed;
    }
    printk("insmod ipfrq module, dev: %s\n", devname);

    return 0;                   /* return 0 for success */
   
failed:
    return -1;
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */
    ipstat_hash_free();
    if (ipstat_cachep) kmem_cache_destroy(ipstat_cachep);
    printk("rmmod ipfrq module\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

module_param(duration, ulong, S_IRUGO);
module_param(keepalive, ulong, S_IRUGO);
module_param(clearcycle, ulong, S_IRUGO);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("ipfrq");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
