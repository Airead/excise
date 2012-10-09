/**
 * @file loopbuf.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/09 11:43:19
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/ctype.h>
#include <linux/netdevice.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/route.h>
#include <net/dst.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter_ipv4/ipt_REJECT.h>
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_extend.h>
#include <net/netfilter/nf_conntrack_acct.h>

/*
 * Macros to help debugging
 */

#define LOOPBUF_DEBUG

#undef PDEBUG             /* undef it, just in case */
#ifdef LOOPBUF_DEBUG
#  ifdef __KERNEL__
/* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_INFO "loopbuf: " fmt, ## args)
#  else
/* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#define VERSION 	"0.00"

#define ADDR_BUFF_SIZE (sizeof("xxx.xxx.xxx.xxx:xxxxx"))
#define DATA_SIZE 1024
#define BUF_SIZE 4096

struct strcb {
    wait_queue_head_t rq;       /* read queue */
    char *address;  /* start of memory */
    int size;   /* maximum number of buffer */
    int start;  /* pointer of the oldest string */
    int end;    /* pointer of new string to write */
    int count;
};


static char loopbuf[BUF_SIZE];
static struct strcb string_cb;

int strcb_init(struct strcb *scb, int size)
{
    memset(scb, 0, sizeof(struct strcb));
    
    scb->address = loopbuf;
    scb->size = BUF_SIZE;
    scb->start = 0;
    scb->end = 0;
    scb->count = 0;

    init_waitqueue_head(&scb->rq);
    return 0;
}

int strcb_write(struct strcb *scb, char *buf, int len)
{
    PDEBUG("into strcb_write\n");

    if (scb->end > scb->start) {
        if (scb->size - scb->end < len + 1) { /* spare buffer in the rear is not enough */
            if (scb->start  < len + 1) {         /* spare buffer in the head is not enough too */
                /* drop this string */
                PDEBUG("drop: scb->end > scb->start, head is not enough!\n");
                goto drop;
            }

            /* store string at address */
            scb->address[scb->end] = -1;
            memcpy(scb->address, buf, len);
            scb->address[len] = '\0';
            scb->end = len + 1;
            goto out;
        }
    } else if (scb->start == scb->end && scb->count != 0) { /* buffer full */
        PDEBUG("drop: scb->end == scb->start, buffer full!\n");
        goto drop;
    } else {
        if (scb->start == scb->end && scb->count == 0) { /* buffer empty */
            if (scb->size - scb->end < len + 1) { /* spare buffer in the rear is not enough */
                scb->address[scb->end] = -1;
                memcpy(scb->address, buf, len);
                scb->address[len] = '\0';
                scb->end = len + 1;
                goto out;
            }
            goto store;
        }
        if (scb->start - scb->end < len + 1) { /* spare buffer in the middle is not enough */
            PDEBUG("drop: scb->end < scb->start, middle is not enough!\n");
            goto drop;
        }
    }
store:
    /* store string at end */
    memcpy(scb->address + scb->end, buf, len);
    scb->address[scb->end + len] = '\0';
    scb->end = scb->end + len + 1;
    
out:
    scb->count += len + 1;
    wake_up_interruptible(&string_cb.rq);
    return len + 1;

drop:
    return -1;
}

/* about /proc */
/**
 * @brief start read /proc (seq file)
 * @param s
 * @param pos not used
 * @return void* read pointer, NULL for end
 *
 * start to read seq file. if buff empty, the user space process will be
 * blocked until write new data.
 */
static void *loopbuf_seq_start(struct seq_file *s, loff_t *pos)
{
    void *readp;
    int i;

    if (string_cb.start == string_cb.end && string_cb.count == 0) { /* empty */
        PDEBUG("start rp == wp\n");
        if (wait_event_interruptible(string_cb.rq, (string_cb.start != string_cb.end))) {
            return NULL;
        }
    }

    if (string_cb.address[string_cb.start] == -1) {
        string_cb.start = 0;
    }
    readp = string_cb.address + string_cb.start;

    /* get next readp */
    i = 0;
    while (string_cb.address[string_cb.start + i] != '\0') {
        i++;
    }

    string_cb.start += i + 1;
    string_cb.count -= i + 1;

    return readp;
}

/**
 * @brief get next read pointer
 * @param s
 * @param v read pointer, not used in current function
 * @param pos not used
 * @return void* next read pointer, NULL for end
 *
 * if buffer is empty, just return NULL to end.
 */
static void *loopbuf_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
    void *readp;
    int i;

    if (string_cb.start == string_cb.end && string_cb.count == 0) { /* empty */
        /* this MUST NOT use if wait_event_interruptible(), otherwise `cat' can not get anything */
        PDEBUG("start rp == wp\n");
        return NULL;
    }

    if (string_cb.address[string_cb.start] == -1) {
        string_cb.start = 0;
    }
    readp = string_cb.address + string_cb.start;
    
    /* get next readp */
    i = 0;
    while (string_cb.address[string_cb.start + i] != '\0') {
        i++;
    }

    string_cb.start += i + 1;
    string_cb.count -= i + 1;

    return readp;
}

static void loopbuf_seq_stop(struct seq_file *s, void *v)
{
	/* Actually, there's nothing to do here */
}

/**
 * @brief just print server ip and port
 * @param s
 * @param v point to server address buffer start
 * @return 
 */
static int loopbuf_seq_show(struct seq_file *s, void *v)
{
    int ret;
    char *buf = v;

    PDEBUG("into seq_show\n");
    PDEBUG("seq_file: size: %lu, count: %lu", s->size, s->count);
    PDEBUG("strcb: size: %d, start: %d, end: %d, count: %d\n", 
           string_cb.size, string_cb.start, string_cb.end, string_cb.count);      
    PDEBUG("[%p] buf: %s\n", buf, buf);
    
    ret = seq_printf(s, "%s\n", buf);
    PDEBUG("seq_printf ret: %d\n", ret);

	return 0;
}

static struct seq_operations loopbuf_seq_ops = {
	.start = loopbuf_seq_start,
	.next  = loopbuf_seq_next,
	.stop  = loopbuf_seq_stop,
	.show  = loopbuf_seq_show
};

/*
 * Now to implement the /proc file we need only make an open
 * method which sets up the sequence operators.
 */
static int loopbuf_proc_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &loopbuf_seq_ops);
}

/*
 * Create a set of file operations for our proc file.
 */
static struct file_operations loopbuf_proc_ops = {
	.owner   = THIS_MODULE,
	.open    = loopbuf_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};

static void loopbuf_create_proc(void)
{
    struct proc_dir_entry *entry;

	entry = create_proc_entry("loopbuf", 0, NULL);
	if (entry)
		entry->proc_fops = &loopbuf_proc_ops;
}

static void loopbuf_remove_proc(void)
{
	/* no problem if it was not registered */
	remove_proc_entry("loopbuf", NULL);
}

static int __init my_init_module(void)
{
    int i, j;
    char *str[] = {
        "hello A",
        "happy happy B",
        "tony tony C",
        "ABCDefghijklmnopqrst",
        NULL
    };

    strcb_init(&string_cb, 4096);
    loopbuf_create_proc();
    
    for (j = 0; j < 100; j++) {
        for (i = 0; str[i] != NULL; i++) {
            strcb_write(&string_cb, str[i], strlen(str[i]));
        }
    }

    printk("insmod loopbuf module\n");


    return 0;                   /* return 0 for success */
   
}

/* Call when module unloaded using 'rmmod' */
static void __exit my_cleanup_module(void)
{
    loopbuf_remove_proc();
    printk("rmmod loopbuf module\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("loopbuf");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
