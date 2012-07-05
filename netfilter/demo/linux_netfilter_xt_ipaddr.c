/**
 * @file linux_netfilter_xt_ipaddr.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/05 10:56:53
 */

#include <linux/ipv6.h>
#include <linux/ip.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/kernel.h>

static struct xt_match ipaddr_mt_reg __read_mostly = {
    .name = "ipaddr",
    .revision = 0,
    .family = NFPROTO_IPV6,
    .match = ipaddr_mt,
    .checkentry = ipaddr_mt_check,
    .destroy = ipaddr_mt_destroy,
    .matchsize = sizeof(struct xt_ipaddr_mtinfo),
    .me = THIS_MODULE,
};

static struct xt_match ipaddr_mt4_reg __read_mostly = {
    .name = "ipaddr",
    .revision = 0,
    .family= NFPROTO_IPV4,
    .match= ipaddr_mt4,
    .matchsize = sizeof(struct xt_ipaddr_mtinfo),
    .me = THIS_MODULE,
};


static int __init ipaddr_mt_init(void)
{
    int ret;

    ret = xt_register_match(&ipaddr_mt_reg);
    if (ret < 0)
        return ret;

    ret = xt_register_match(&ipaddr_mt4_reg);
    if (ret < 0) {
        xt_unregister_match(&ipaddr_mt_reg);
        return ret;
    }

    return 0;
}

static void __exit ipaddr_mt_exit(void)
{
    xt_unregister_match(&ipaddr_mt_reg);
    xt_unregister_match(&ipaddr_mt4_reg);
}

#if 0
struct xt_action_param {
    const struct xt_match *match;
    const void *matchinfo;
    const struct net_device *in, *out;
    int fragoff;
    unsigned int thoff;
    unsigned int hook;
    uint8_t family;
    bool hotdrop;
};
#endif

static bool ipaddr_mt*(const struct sk_buff *skb, struct xt_action_param *par)
{
    const struct xt_ipaddr_mtinfo *info = par->matchinfo;
    const struct ipv6hdr *iph = ipv6_hdr(skb);

    pr_info(
        "xt_ipaddr: IN=%s OUT=%s "
        "SRC=" NIP6_FMT " DST=" NIP6_FMT " "
        "IPSRC=" NIP6_FMT " IPDST=" NIP6_FMT "\n",
        (par->in != NULL) ? par->in->name : "",
        (par->out != NULL) ? par->out->name : "",
        NIP6(iph->saddr), NIP6(iph->daddr),
        NIP6(info->src), NIP6(info->dst)
        );
    
    if (info->flags & XT_IPADDR_SRC)
        if ((ipv6_addr_cmp(&iph->saddr, &info->src.in6) != 0) ^
            !!(info->flags & XT_IPADDR_SRC_INV)) {
            pr_notice("src IP - no match\n");
            return false;
        }

    if (info->flags & XT_IPADDR_DST)
        if ((ipv6_addr_cmp(&iph->daddr, &info->dst.in6) != 0) ^
            !!(info->flags & XT_IPADDR_DST_INV)) {
            pr_notice("dst IP - no match\n");
            return false;
        }
    
    return true;
}

static int ipaddr_mt_check(const struct xt_mtchk_param *par)
{
    const struct xt_ipaddr_mtinfo *info = par->matchinfo;
    pr_info("Added a rule with -m ipaddr in the %s table; this rule is "
            "reachable through hooks 0x%x\n",
            par->table, par->hook_mask);
    if (!(info->flags & (XT_IPADDR_SRC | XT_IPADDR_DST))) {
        pr_info("not testing for anything\n");
        return -EINVAL;
    }
    if (ntohl(info->src.ip6[0]) == 0x20010DB8) {
        /* Disallow test network 2001:db8::/32 */
        pr_info("I’m sorry, Dave. "
                "I’m afraid I can’t let you do that.\n");
        return -EPERM;
    }
    return 0;
}

static void ipaddr_mt_destroy(const struct xt_mtdtor *par)
{
    const struct xt_ipaddr_mtinfo *info = par->matchinfo;
    pr_info("Test for address " NIP6_FMT " removed\n",
            NIP6(info->src.ip6));
}

static bool ipaddr_mt4(const struct sk_buff *skb,
                       const struct xt_action_param *par)
{
    const struct xt_ipaddr_mtinfo *info = par->matchinfo;
    const struct iphdr *iph = ip_hdr(skb);
    if (info->flags & XT_IPADDR_SRC)
        if ((iph->saddr != info->src.ip) ^
            !!(info->flags & XT_IPADDR_SRC_INV))
            return false;
    if (info->flags & XT_IPADDR_DST)
        if ((iph->daddr != info->dst.ip) ^
            !!(info->flags & XT_IPADDR_DST_INV))
            return false;
    return true;
}


module_init(ipaddr_mt_init);
module_exit(ipaddr_mt_exit);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("Xtables: Match source/destination address");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip6t_ipaddr");
