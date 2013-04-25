/**
 * @file ipt_MYSNAT.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/03/19 10:06:20
 */

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
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

#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_core.h>
#include <net/netfilter/nf_nat_rule.h>


/* Source NAT */
static unsigned int
ipt_mysnat_target(struct sk_buff *skb, const struct xt_action_param *par)
{
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	NF_CT_ASSERT(par->hooknum == NF_INET_POST_ROUTING ||
		     par->hooknum == NF_INET_LOCAL_IN);

	ct = nf_ct_get(skb, &ctinfo);

	/* Connection must be valid and new. */
	NF_CT_ASSERT(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
			    ctinfo == IP_CT_RELATED_REPLY));
	NF_CT_ASSERT(par->out != NULL);

	return nf_nat_setup_info(ct, &mr->range[0], NF_NAT_MANIP_SRC);
}

static int ipt_mysnat_checkentry(const struct xt_tgchk_param *par)
{
	const struct nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	/* Must be a valid range */
	if (mr->rangesize != 1) {
		pr_info("SNAT: multiple ranges no longer supported\n");
		return -EINVAL;
	}
	return 0;
}


static struct xt_target ipt_mysnat_reg __read_mostly = {
	.name		= "MYSNAT",       /* name is the name of the target that you define */
	.target		= ipt_mysnat_target,
	.targetsize	= sizeof(struct nf_nat_ipv4_multi_range_compat),
	.table		= "nat",
    /*
     * hooks is a bitmask and may contain zero or more of the following flags:
     *   • 1 << NF_INET_PRE_ROUTING
     *   • 1 << NF_INET_LOCAL_IN
     *   • 1 << NF_INET_FORWARD
     *   • 1 << NF_INET_LOCAL_OUT
     *   • 1 << NF_INET_POST_ROUTING
     */
	.hooks		= (1 << NF_INET_POST_ROUTING) | (1 << NF_INET_LOCAL_IN),
	/* Called when user tries to insert an entry of this type:
           hook_mask is a bitmask of hooks from which it can be
           called. */
	/* Should return 0 on success or an error code otherwise (-Exxxx). */
	.checkentry	= ipt_mysnat_checkentry,
	.family		= AF_INET,
};

static int __init mysnat_target_init(void)  
{  
        return xt_register_target(&ipt_mysnat_reg);  
}  
  
static void __exit mysnat_target_exit(void)  
{  
        xt_unregister_target(&ipt_mysnat_reg);  
}  

module_init(mysnat_target_init);  
module_exit(mysnat_target_exit);  
