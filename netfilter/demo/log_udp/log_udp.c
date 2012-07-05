/**
 * @file log_udp.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/05 16:11:50
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>

static struct nf_hook_ops nfho; /* struct holding set of hook function optionsj */
struct sk_buff *sock_buff;
struct udphdr *udp_header;      /* udp header struct (not used) */
struct iphdr *ip_header;        /* ip header struct */

/* function to be called by hook */
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    sock_buff = skb;

    ip_header = ip_hdr(sock_buff); /* grab network header */
    if (!sock_buff) {
        return NF_ACCEPT;
    }
    
    printk(KERN_INFO "protocol num = %d: ", ip_header->protocol);

    if (ip_header->protocol == 17) {
        udp_header = (struct udphdr *)skb_transport_header(sock_buff); /* grab transport header */
        printk(KERN_INFO "got udp packet \n");                        /* log we've get udp packet */
        return NF_ACCEPT;
    }
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

