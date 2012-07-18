/**
 * @file dnat.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/17 12:17:36
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/route.h>
#include <net/dst.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_REJECT.h>

struct m_table {
    __be32 addr;
    __be16 port;
};

static struct nf_hook_ops nfho; /* struct holding set of hook function optionsj */
static struct sk_buff *sock_buff;
static struct iphdr *ip_header;        /* ip header struct */
static struct tcphdr *tcp_header;      /* tcp header struct */

static struct m_table match_table;
static __be32 daddr, src_addr;
static __be16 dport;

/* 1 for match, 0 for not match */
static int match_srv(struct m_table *mt, __be32 m_daddr, __be16 port)
{
//   int ret;

//    printk(KERN_INFO "mtip: %pI4:%u, m_daddrip: %pI4:%u\n", &mt->addr, ntohs(mt->port), &m_daddr, ntohs(port));

    if (mt->addr == m_daddr && mt->port == port) {
//        printk(KERN_INFO "match\n");    
        return 1;
    }
    
    return 0;
}

static int my_dnat(struct sk_buff *skb, __be32 daddr, __be16 port)
{
    printk(KERN_INFO "dnat %pI4:%u to %pI4:%u\n", &ip_header->daddr, ntohs(tcp_header->dest), &daddr, ntohs(port));

    ip_header->daddr = daddr;
    tcp_header->dest = port;

    tcp_header->check = 0;
    skb->csum = skb_checksum_complete(skb);
    /* tcp_header->check = tcp_v4_check(sizeof(struct tcphdr),
     *                                  ip_header->saddr, ip_header->daddr,
     *                                  csum_partial(tcp_header,
     *                                               sizeof(struct tcphdr), 0)); */
    printk(KERN_INFO "chksum: %x\n", ip_header->check);

    /* ip_header->check = ip_fast_csum((void *)ip_header, ip_header->ihl);
     * printk(KERN_INFO "chksum: %x\n", ip_header->check);
     * skb->ip_summed = CHECKSUM_COMPLETE; */

    return 0;
}

/* function to be called by hook */
static unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    char *payload;

    sock_buff = skb;

    ip_header = ip_hdr(sock_buff); /* grab network header */

    if (ip_header->saddr != src_addr) {
        return NF_ACCEPT;
    }

    if (!sock_buff) {
        return NF_ACCEPT;
    }
    
    if (ip_header->protocol != 6) {       /* not tcp, pass */
        return NF_ACCEPT;
    }

    /* get header size */
    tcp_header = (void *)sock_buff->data + ip_header->ihl * 4;
    payload = (char *)tcp_header + tcp_header->doff * 4;

    if (skb_linearize(sock_buff) != 0) { /* linerize failed */
        printk("linerize failed\n");
        return NF_ACCEPT;
    }
    

    if (payload[0] == 'H' && payload[1] == 'T' && 
        payload[2] == 'T' && payload[3] == 'P') {
        printk(KERN_INFO "http_server %pI4:%u\n", 
               &ip_header->saddr, ntohs(tcp_header->source));
        //add to list

    }

//    printk(KERN_INFO "source: %u, dest: %u\n", ntohs(tcp_header->source), ntohs(tcp_header->dest));
    
    if (match_srv(&match_table, ip_header->daddr, tcp_header->dest) != 0) {
        if (my_dnat(sock_buff, daddr, dport) < 0) {
            printk(KERN_ALERT "my dnat error\n");
        }
    }

    return NF_ACCEPT;
}

static int __init my_init_module(void)
{
    int ret;
//    char *ip = "220.181.111.147";
//    char *ip = "61.135.169.125";
    char *ip = "12.12.12.12";
    char *ip_src = "192.168.1.100";
    char *ip_dst = "220.181.111.147";

    ret = in4_pton(ip_src, sizeof("xxx.xxx.xxx.xxx"), (void *)&src_addr, '\0', NULL);
    if (!ret) {
        printk(KERN_ALERT "inval ip addr， src_addr\n");
        return -ret;
    }

    ret = in4_pton(ip, sizeof("xxx.xxx.xxx.xxx"), (void *)&match_table.addr, '\0', NULL);
    if (!ret) {
        printk(KERN_ALERT "inval ip addr, mt_addr\n");
        return -ret;
    }
    match_table.port = htons(33334);

    ret = in4_pton(ip_dst, sizeof("xxx.xxx.xxx.xxx"), (void *)&daddr, '\0', NULL);
    if (!ret) {
        printk(KERN_ALERT "inval ip addr, daddr\n");
        return -ret;
    }
    dport = htons(80);

    nfho.hook = hook_func;      /* function to call when conditions below met */
    nfho.hooknum = NF_INET_PRE_ROUTING;// | NF_INET_LOCAL_OUT | NF_INET_LOCAL_IN; /* called right after packet recieved, first hook in Netfilter */
    nfho.pf = PF_INET;                /* IPV4 packets */
    nfho.priority = NF_IP_PRI_MANGLE; /* set to highest priority over all other hook functions */
    nf_register_hook(&nfho);         /* register hook */

    printk("insmod dnat\n");

    return 0;                   /* return 0 for success */
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */

    printk("rmmod dnat\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("dnat");
MODULE_LICENSE("GPL");
MODULE_ALIAS("dnat");
