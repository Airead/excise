/**
 * @file genpkt.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/01 15:39:38
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/if_arp.h>
#include <linux/errno.h>
#include <linux/ip.h>
#include <linux/udp.h>

#define VERSION "0.01"

//20:6a:8a:64:eb:84
static __u8 mac_dst[6] = {0x20, 0x6a, 0x8a, 0x64, 0xeb, 0x84};
static char mac_src_type[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00};
static char *ip_dst = "192.168.1.12";
static char *ip_src = "0.0.0.0";

netdev_tx_t (*xmit)(struct sk_buff *, struct net_device *);

static __u16 __checksum(u16 *addr, int count)
{
    u32 sum = 0;
    int i;

    for (i = 0; i < count; i+=6) {
        pr_info("%x %x %x %x %x %x\n", htons(addr[i]),htons(addr[i+1]),htons(addr[i+2]),htons(addr[i+3]),htons(addr[i+4]),htons(addr[i+5]));
    }

    for (i = 0; i < count; i++) {
        sum += htons(addr[i]);
        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);
    }

    return sum;

}

static __u16 checksum(__be32 *saddr, __be32 *daddr, u16 protocol, u16 *addr,  __u16 len)
{
    struct udphdr *udph = (struct udphdr *)addr;
    char *payload;
    u32 sum = 0;
//    int i;
    
    pr_info("len = %u\n", len);
    pr_info("checksum: udph->source = %u, udph->dest = %u, udph->len = %u, udph->check = %u\n", 
            ntohs(udph->source), ntohs(udph->dest), ntohs(udph->len), udph->check);
    pr_info("saddr: %u, daddr %u, proto %u, addr %p, len %u\n",
            *saddr, *daddr, protocol, addr, len); 
    payload = (char *)addr + 8;

    /* for (i = 0; i < 96; i+=6) {
     *     pr_info("%d %d %d %d %d %d\n", payload[i],payload[i+1],payload[i+2],payload[i+3],payload[i+4],payload[i+5]);
     * } */

    pr_info("saddr check 2 \n");
    sum += __checksum((u16 *)saddr, 2);
    sum += (sum >> 16);

    pr_info("daddr check 2 \n");
    sum += __checksum((u16 *)daddr, 2);
    sum += (sum >> 16);

    pr_info("len check 1 \n");
    sum += __checksum(&udph->len, 1);
    sum += (sum >> 16);

    pr_info("protocol check 1 \n");
    pr_info("%04x", protocol);
    sum += protocol;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    pr_info("addr check %u\n", len / 2);
    sum += __checksum(addr, len / 2);
    sum += (sum >> 16);

    return ~sum;
}

static struct sk_buff *fill_packet_ipv4(struct net_device *odev)
{
	struct sk_buff *skb = NULL;
    struct iphdr *iph;
    struct udphdr *udph;
    __u8 *eth;
    char *payload, *str;
    int ret;
    int ethlen, datalen, skblen, iplen;
    __u16 check;

    /* just align 16 */
    ethlen = (odev->hard_header_len + 16) & ~0xf;
    pr_info("odev->hard_header_len = %d, ethlen = %d\n", 
            odev->hard_header_len, ethlen);
    datalen = 96;
    skblen = ethlen + sizeof(struct iphdr) + sizeof(struct udphdr) + datalen;
    skb = __netdev_alloc_skb (odev, skblen, GFP_NOWAIT);
    pr_info("skblen = %u, skb->len = %u\n", skblen, skb->len);

	if (!skb) {
		pr_err("No memory");
		return NULL;
	}

    pr_info("before prefetchw(skb->data): skb->tail = %u, skb->end = %u\n", 
            skb->tail, skb->end);
	prefetchw(skb->data);

    pr_info("before skb_reserve: skb->tail = %u, sizeof struct iphdr = %lu\n", 
            skb->tail, sizeof(struct iphdr));
    
	skb_reserve(skb, ethlen);

	/*  Reserve for ethernet and IP header  */
	eth = (__u8 *) skb_push(skb, 14); 

	skb->network_header = skb->tail;
    pr_info("skb->tail = %u, sizeof struct iphdr = %lu\n", 
            skb->tail, sizeof(struct iphdr));
	skb->transport_header = skb->network_header + sizeof(struct iphdr);
	skb_put(skb, sizeof(struct iphdr) + sizeof(struct udphdr));

    /* not set queue_mapping, i don't know what will happen  */
//	skb_set_queue_mapping(skb, queue_map);

	skb->priority = 0;

	iph = ip_hdr(skb);
	udph = udp_hdr(skb);

    /* set eth header */
	memcpy(eth, mac_dst, 6);
    memcpy(&eth[6], mac_src_type, 8);

    /* fed ip header */
	iph->ihl = 5;
	iph->version = 4;
	iph->ttl = 32;
	iph->tos = 0;
	iph->protocol = IPPROTO_UDP;	/* UDP */
    iph->id = 122;
	iph->frag_off = 0;
	iplen = sizeof(struct iphdr) + sizeof(struct udphdr) + 96;
	iph->tot_len = htons(iplen);

    ret = in4_pton(ip_src, sizeof("xxx.xxx.xxx.xxx"), (void *)&iph->saddr, '\0', NULL);
    if (!ret) {
        printk(KERN_ALERT "inval ip addr， src_addr\n");
        goto skb_free;
    }

    ret = in4_pton(ip_dst, sizeof("xxx.xxx.xxx.xxx"), (void *)&iph->daddr, '\0', NULL);
    if (!ret) {
        printk(KERN_ALERT "inval ip addr， src_addr\n");
        goto skb_free;
    }

	iph->check = 0;
	iph->check = ip_fast_csum((void *)iph, iph->ihl);

	udph->source = htons(88);
	udph->dest = htons(1199);
	udph->len = htons(iplen - 20);	/* DATA + udphdr */
	udph->check = 0;	/* No checksum */

    /* calculate check sum */
    payload = skb_put(skb, 96);
    memset(payload, 0, 96);
    str = "I am Airead Fan";
    memcpy(payload, str, strlen(str));


    skb->csum_start = skb_transport_header(skb) - skb->head;
    pr_info("skb->transport_header = %u\n", skb->transport_header);
    skb->csum_offset = offsetof(struct udphdr, check);
    pr_info("skb->csum_start = %u, skb->csum_offset = %u, skb->len = %u, udph->len = %u\n", 
            skb->csum_start, skb->csum_offset, skb->len, ntohs(udph->len));
    
    check = csum_tcpudp_magic(iph->saddr, iph->daddr, ntohs(udph->len), IPPROTO_UDP, 0);
    pr_info("check = %X, ~check= %x\n", check, (u16)~check);

    skb->csum_start = skb_transport_header(skb) - skb->head - 7;
    check = csum_tcpudp_magic(iph->saddr, iph->daddr, ntohs(udph->len), IPPROTO_UDP, 0);
    pr_info("change start-7: check = %X, ~check= %x\n", check, (u16)~check);

    pr_info("udph->chekc = %x\n", udph->check);
    udph->check = 0;
    check = csum_tcpudp_magic(iph->saddr, iph->daddr, ntohs(udph->len), IPPROTO_UDP, 0);
    pr_info("change start-7: check = %X, ~check= %x\n", check, (u16)~check);
    
    check = checksum(&iph->saddr, &iph->daddr, 17, (u16 *)udph, ntohs(udph->len));
    pr_info("my checksum: check = %X, ~check= %x\n", check, (u16)~check);

    udph->check = htons(check);


	skb->protocol = 0x6000;
	skb->mac_header = skb->network_header;
	skb->dev = odev;
	skb->pkt_type = PACKET_HOST;

	return skb;

skb_free:
    kfree_skb(skb);
    return NULL;
}

static int genpkt_xmit(const char *ifname)
{
    struct net_device *odev = NULL;
    struct sk_buff *skb;
	struct netdev_queue *txq;
    u16 queue_map;
    int err, ret;

    /* get output device */
    odev = dev_get_by_name(&init_net, ifname);
	if (!odev) {
		pr_err("no such netdevice: \"%s\"\n", ifname);
		return -ENODEV;
	}

	if (odev->type != ARPHRD_ETHER) {
		pr_err("not an ethernet device: \"%s\"\n", ifname);
		err = -EINVAL;
        goto dev_put;
	} else if (!netif_running(odev)) {
		pr_err("device is down: \"%s\"\n", ifname);
		err = -ENETDOWN;
        goto dev_put;
	}

    /* get xmit function */
    xmit = odev->netdev_ops->ndo_start_xmit;
    
    /* If device is offline, then don't send */
	if (unlikely(!netif_running(odev) || !netif_carrier_ok(odev))) {
        pr_err("device offline\n");
        goto dev_put;
	}

    /* get one skb */
    skb = fill_packet_ipv4(odev);
    if (skb == NULL) {
        pr_err("ERROR: couldn't allocate skb in fill_packet\n");
        goto dev_put;
    }

    queue_map = smp_processor_id();
	txq = netdev_get_tx_queue(odev, queue_map);
	__netif_tx_lock_bh(txq);
	atomic_inc(&(skb->users));

    ret = (*xmit)(skb, odev);

	switch (ret) {
	case NETDEV_TX_OK:
        pr_info("send skb OK\n");
		break;
	default: /* Drivers are not supposed to return other values! */
		if (net_ratelimit())
			pr_info("pktgen: %s xmit error: %d\n",
				odev->name, ret);
		/* fallthru */
	case NETDEV_TX_LOCKED:
	case NETDEV_TX_BUSY:
        atomic_dec(&(skb->users));
        pr_err("locked or busy\n");
	}

	__netif_tx_unlock_bh(txq);

    kfree_skb(skb);
dev_put:
    dev_put(odev);
    return err;
}

static int __init genpkt_init(void)
{
	pr_info("genpkt module init\n");

    genpkt_xmit("eth0");

	return 0;
}

static void __exit genpkt_cleanup(void)
{
    pr_info("genpkt module exit\n");
}

module_init(genpkt_init);
module_exit(genpkt_cleanup);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("Packet Generator");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
