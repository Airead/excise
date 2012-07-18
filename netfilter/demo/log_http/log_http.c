/**
 * @file log_http.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/06 10:30:58
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
static struct tcphdr *tcp_header;      /* tcp header struct */
static char buf[21];

/* function to be called by hook */
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    __u8 i;
    __u16 len;
    sock_buff = skb;

    ip_header = ip_hdr(sock_buff); /* grab network header */
    if (!sock_buff) {
        return NF_ACCEPT;
    }
    
    if (ip_header->protocol != 6) {       /* not tcp, pass */
        return NF_ACCEPT;
    }

    /* get header size */
    tcp_header = (void *)sock_buff->data + ip_header->ihl * 4;

    printk(KERN_INFO "\n"
           "version: %u, header length: %u, total len: %u\n"
           "ttl: %u, scr: %pI4:%u, dst: %pI4:%u\n"
           "ip_header->lhl: %u, tcp_header->doff: %u\n",
           ip_header->version, ip_header->ihl, ntohs(ip_header->tot_len),
           ip_header->ttl, &ip_header->saddr, ntohs(tcp_header->source),
           &ip_header->daddr, ntohs(tcp_header->dest),
           ip_header->ihl, tcp_header->doff);

    if (skb_linearize(sock_buff) != 0) { /* linerize failed */
        return NF_ACCEPT;
    }

    len = 0;
    while (len < sock_buff->len) {
        for (i = 0; i < 20; i++) {
            if ((sock_buff->data[len] > 'A' && sock_buff->data[len] < 'Z') ||
                (sock_buff->data[len] > 'a' && sock_buff->data[len] < 'z')) {
                buf[i] = sock_buff->data[len];
            } else {
                buf[i] = '.';
            }
            len++;
        }
        buf[i] = '\0';
        printk("content: %s\n", buf);
    }

    return NF_ACCEPT;
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
MODULE_DESCRIPTION("log http");
MODULE_LICENSE("GPL");
MODULE_ALIAS("log http");
