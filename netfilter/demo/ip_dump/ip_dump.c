/**
 * @file ip_dump.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/05 16:33:51
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/tcp.h>
#include <linux/ip.h>

static struct nf_hook_ops nfho; /* struct holding set of hook function optionsj */
static struct sk_buff *sock_buff;
static struct iphdr *ip_header;        /* ip header struct */
static struct tcphdr *tcp_header;

#if 0
struct iphdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	ihl:4,
		version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
	__u8	version:4,
  		ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	__u8	tos;
	__be16	tot_len;
	__be16	id;
	__be16	frag_off;
	__u8	ttl;
	__u8	protocol;
	__sum16	check;
	__be32	saddr;
	__be32	daddr;
	/*The options start here. */
};
#endif

/* function to be called by hook */
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    sock_buff = skb;

    ip_header = ip_hdr(sock_buff); /* grab network header */
    if (!sock_buff) {
        return NF_ACCEPT;
    }

    tcp_header = tcp_hdr(sock_buff);
    if (!sock_buff) {
        return NF_ACCEPT;
    }
    
    printk(KERN_INFO "\n"
           "version: %u, header length: %u, total len: %u\n"
           "ttl: %u, scr: %pI4:%u, dst: %pI4:%u\n",
           ip_header->version, ip_header->ihl, ntohs(ip_header->tot_len),
           ip_header->ttl, &ip_header->saddr, ntohs(tcp_header->source),
           &ip_header->daddr, ntohs(tcp_header->dest));

    return NF_ACCEPT;                        /* dorps the packet */
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

