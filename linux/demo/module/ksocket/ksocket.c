#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/socket.h>
#include <net/sock.h>

static struct socket *sock;
static struct work_struct work;

static int udp_sendto(struct socket *sock, void * buff, size_t len, 
                      unsigned flags, struct sockaddr *addr, int addr_len)
{
    struct kvec vec;
    struct msghdr msg;
    vec.iov_base=buff;
    vec.iov_len=len;

    memset(&msg, 0x00, sizeof(msg));
    msg.msg_name=addr;
    msg.msg_namelen=addr_len;
    msg.msg_flags = flags | MSG_DONTWAIT;
    return kernel_sendmsg(sock, &msg, &vec, 1, len);
} 

static char buffer[128];

static void sendmsg(struct work_struct *dummy)
{
    int n;
    struct sockaddr_in addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1000);
    addr.sin_addr.s_addr = in_aton("61.139.2.69");
    n = udp_sendto(sock, buffer, 128, 0, (struct sockaddr *)&addr,
                   sizeof(addr));
    printk("send %i bytes/n", n);
}

static int socket_init(void)
{
    INIT_WORK(&work, sendmsg);
    sock_create_kern(PF_INET, SOCK_DGRAM, 0, &sock);
    schedule_work(&work);
    return 0;
}

static void socket_exit(void)

{
    sock_release(sock);
}

module_init(socket_init);

module_exit(socket_exit);
