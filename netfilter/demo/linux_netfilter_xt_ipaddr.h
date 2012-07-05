#ifndef _LINUX_NETFILTER_XT_IPADDR_H_
#define _LINUX_NETFILTER_XT_IPADDR_H_ 1

enum {
    XT_IPADDR_SRC = 1 << 0,
    XT_IPADDR_DST = 1 << 1,
    XT_IPADDR_SRC_INV = 1 << 2,
    XT_IPADDR_DST_INV = 1 << 3,
};

stuct xt_ipaddr_mtinfo {
    union nf_inet_addr src, dst;
    __u8 flags;
}


#endif /* _LINUX_NETFILTER_XT_IPADDR_H_ */
