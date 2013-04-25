/**
 * @file record_http_server.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/06 14:18:41
 */

#if 0
HTTP/1.1 302 Moved Temporarily
Server: nginx/1.2.0
Date: Fri, 06 Jul 2012 08:14:35 GMT
    Content-Type: text/html
    Content-Length: 160
    Connection: keep-alive
    Location: http://www.baidu.com
#endif

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
#ifdef CONFIG_BRIDGE_NETFILTER
#include <linux/netfilter_bridge.h>
#endif

static struct nf_hook_ops nfho; /* struct holding set of hook function optionsj */
static struct sk_buff *sock_buff;
static struct iphdr *ip_header;        /* ip header struct */
static struct tcphdr *tcp_header;      /* tcp header struct */

static char h302[] = "HTTP/1.0 302 Moved Temporarily\r\n"
    "Server: nginx/1.2.0\r\n"
    "Date: Fri, 06 Jul 2012 08:14:35 GMT\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 160\r\n"
    "Connection: keep-alive"
    "Location: http://www.baidu.com";

static void send_reset(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *nskb;
	const struct iphdr *oiph;
	struct iphdr *niph;
	const struct tcphdr *oth;
	struct tcphdr _otcph, *tcph;
	unsigned int addr_type;

	oth = skb_header_pointer(oldskb, ip_hdrlen(oldskb),
				 sizeof(_otcph), &_otcph);
	if (oth == NULL)
		return;

	/* No RST for RST. */
	if (oth->rst)
		return;

	/* Check checksum */
	if (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
		return;
	oiph = ip_hdr(oldskb);

	nskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
			 LL_MAX_HEADER, GFP_ATOMIC);
	if (!nskb)
		return;

	skb_reserve(nskb, LL_MAX_HEADER);

	skb_reset_network_header(nskb);
	niph = (struct iphdr *)skb_put(nskb, sizeof(struct iphdr));
	niph->version	= 4;
	niph->ihl	= sizeof(struct iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= IPPROTO_TCP;
	niph->check	= 0;
	niph->saddr	= oiph->daddr;
	niph->daddr	= oiph->saddr;

	tcph = (struct tcphdr *)skb_put(nskb, sizeof(struct tcphdr));
	memset(tcph, 0, sizeof(*tcph));
	tcph->source	= oth->dest;
	tcph->dest	= oth->source;
	tcph->doff	= sizeof(struct tcphdr) / 4;

	if (oth->ack)
		tcph->seq = oth->ack_seq;
	else {
		tcph->ack_seq = htonl(ntohl(oth->seq) + oth->syn + oth->fin +
				      oldskb->len - ip_hdrlen(oldskb) -
				      (oth->doff << 2));
		tcph->ack = 1;
	}

	tcph->rst	= 1;
	tcph->check	= tcp_v4_check(sizeof(struct tcphdr),
				       niph->saddr, niph->daddr,
				       csum_partial(tcph,
						    sizeof(struct tcphdr), 0));

	addr_type = RTN_UNSPEC;
	if (hook != NF_INET_FORWARD
#ifdef CONFIG_BRIDGE_NETFILTER
	    || (nskb->nf_bridge && nskb->nf_bridge->mask & BRNF_BRIDGED)
#endif
	   )
		addr_type = RTN_LOCAL;

	/* ip_route_me_harder expects skb->dst to be set */
	skb_dst_set(nskb, dst_clone(skb_dst(oldskb)));

	if (ip_route_me_harder(nskb, addr_type))
		goto free_nskb;

	niph->ttl	= dst_metric(skb_dst(nskb), RTAX_HOPLIMIT);
	nskb->ip_summed = CHECKSUM_NONE;

	/* "Never happens" */
	if (nskb->len > dst_mtu(skb_dst(nskb)))
		goto free_nskb;

	nf_ct_attach(nskb, oldskb);

//	ip_local_out(nskb);
	return;

 free_nskb:
	kfree_skb(nskb);
}

static unsigned int send_reset2(struct sk_buff *oldskb, int hook)
{
	struct sk_buff *newskb;
    struct iphdr *oldip, *newip;
	struct tcphdr oldtcp_buf, *oldtcp;
	unsigned int addr_type;

    if (skb_linearize(oldskb) < 0) {
        printk("skb_linerize(oldskb) < 0; DROP)");
        return 1;
    }

    oldip = ip_hdr(oldskb);
    oldtcp = skb_header_pointer(oldskb, sizeof(struct tcphdr), sizeof(struct tcphdr), &oldtcp_buf);

#if 0
    printk(KERN_INFO "\n"
           "version: %u, header length: %u, total len: %u\n"
           "ttl: %u, scr: %pI4:%u, dst: %pI4:%u\n"
           "ip_header->lhl: %u, oldtcp->doff: %u\n",
           oldip->version, oldip->ihl, ntohs(oldip->tot_len),
           oldip->ttl, &oldip->saddr, ntohs(oldtcp->source),
           &oldip->daddr, ntohs(oldtcp->dest),
           oldip->ihl, oldtcp->doff);
#endif
    
    if (oldtcp == NULL)

        return 1;
    
    newskb = alloc_skb(sizeof(struct iphdr) + sizeof(struct tcphdr) +
                       LL_MAX_HEADER, GFP_ATOMIC);
    if (newskb == NULL)
        return 1;
    skb_reserve(newskb, LL_MAX_HEADER);

    skb_reset_network_header(newskb);
	niph->version	= 4;
	niph->ihl	= sizeof(struct iphdr) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->frag_off	= htons(IP_DF);
	niph->protocol	= IPPROTO_TCP;
	niph->check	= 0;
	newip->saddr = oldip->saddr;
	newip->daddr = oldip->daddr;

    skb_reset_transport_header(newskb);
    newtcp = (void *)skb_put(newskb, sizeof(struct tcphdr));
    memset(newtcp, 0, sizeof(*newtcp));
    newtcp->source = oldtcp->source;
    newtcp->dest = oldtcp->source;
    newtcp->doff = sizeof(struct tcphdr) / 4;
    if (oldtcp->ack) {
        newtcp->ack = oldtcp->ack;
#if 0
    } else {
        newtcp->ack_seq = htonl(ntohl(oldtcp->seq) + oldtcp->syn + oldtcp->fin +
                                oldskb->len - ip_hdrlen(oldskb) - (oldskb->doff << 2));
        tcph->ack = 1;
#endif
    }
    newtcp->rst = 1;
    
    addr_type = RTN_UNSPEC;

    newtcp->check = tcp_v4_check(sizeof(struct tcphdr),
                                 newip->saddr, newip->daddr,
                                 csum_partial(newtcp, sizeof(struct tcphdr), 0));
}

/* function to be called by hook */
static unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in,
                       const struct net_device *out, int (*okfn)(struct sk_buff *))
{
    char *payload;

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
    payload = (char *)tcp_header + tcp_header->doff * 4;

    if (skb_linearize(sock_buff) != 0) { /* linerize failed */
        return NF_ACCEPT;
    }
    
    if (payload[0] == 'H' && payload[1] == 'T' && 
        payload[2] == 'T' && payload[3] == 'P') {
        printk(KERN_INFO "http_server %pI4:%u\n", 
               &ip_header->saddr, ntohs(tcp_header->source));
        
//        send_reset(sock_buff, hooknum);
        send_reset2(sock_buff, hooknum);
        return NF_DROP;
    }

    return NF_ACCEPT;
}

static int __init my_init_module(void)
{
    nfho.hook = hook_func;      /* function to call when conditions below met */
    nfho.hooknum = NF_INET_PRE_ROUTING; /* called right after packet recieved, first hook in Netfilter */
    nfho.pf = PF_INET;                /* IPV4 packets */
    nfho.priority = NF_IP_PRI_MANGLE; /* set to highest priority over all other hook functions */
    nf_register_hook(&nfho);         /* register hook */

    printk("insmod modify_package\n");

    return 0;                   /* return 0 for success */
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    nf_unregister_hook(&nfho);  /* cleanup - unregister hook */

    printk("rmmod modify_package\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("log http");
MODULE_LICENSE("GPL");
MODULE_ALIAS("log http");
