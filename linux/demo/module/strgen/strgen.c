/**
 * @file strgen.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/07/18 15:36:09
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>		/* everything... */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <asm/uaccess.h>	/* copy_*_user */

#include "strgen.h"

#define VERSION 	"0.00"


int strgen_major = 0;           
int strgen_minor = 0;
int strgen_nr_devs = 1;         /* allocate device numbers */

static struct strgen_dev *strgen_devices;     /* allocated in strgen_init_module */
 
/*
 * Open and close
 */
int strgen_open(struct inode *inode, struct file *filp)
{
	struct strgen_dev *dev; /* device information */

	dev = container_of(inode->i_cdev, struct strgen_dev, cdev);
	filp->private_data = dev; /* for other methods */

	return 0;          /* success */
}

int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/*
 * Data management: read and write
 */
ssize_t strgen_read(struct file *filp, char __user *buf, size_t count,
                    loff_t *f_pos)
{	
    ssize_t retval = 0;
//    struct strgen_dev *dev = filp->private_data;

    if (copy_to_user(buf, "Airead Fan\n", 12)) {
		retval = -EFAULT;
		goto out;
    }

    *f_pos += count;
    retval = count;

out:
	return retval;
}

ssize_t strgen_write(struct file *filp, const char __user *buf, size_t count,
                loff_t *f_pos)
{
    return 0;
}

struct file_operations strgen_fops = {
	.owner =    THIS_MODULE,
    .open =     strgen_open,
    .read =     strgen_read,
    /* .llseek =   scull_llseek,
     * .write =    scull_write,
     * .unlocked_ioctl =    scull_ioctl,
	 * .release =  scull_release, */
};
/*
 * Set up the char_dev structure for this device.
 */
static void strgen_setup_cdev(struct strgen_dev *dev)
{
	int err, devno = MKDEV(strgen_major, strgen_minor);
    
	cdev_init(&dev->cdev, &strgen_fops);
	dev->cdev.owner = THIS_MODULE;
	err = cdev_add (&dev->cdev, devno, 1);
	/* Fail gracefully if need be */
	if (err)
		printk(KERN_NOTICE "Error %d adding strgen", err);
}

/*
 * The cleanup function is used to handle initialization failures as well.
 * Thefore, it must be careful to work correctly even if some of the items
 * have not been initialized
 */
void strgen_cleanup_module(void)
{
	int i;
	dev_t devno = MKDEV(strgen_major, strgen_minor);

	/* Get rid of our char dev entries */
	if (strgen_devices) {
		for (i = 0; i < strgen_nr_devs; i++) {
			cdev_del(&strgen_devices[i].cdev);
		}
		kfree(strgen_devices);
	}

	/* cleanup_module is never called if registering failed */
	unregister_chrdev_region(devno, strgen_nr_devs);
}

static int __init strgen_init(void)
{
    int ret;
    dev_t dev;

	printk(KERN_INFO "start initilaize string generator\n");

    /* Get device major numbers dynamically */

    /**
     * alloc_chrdev_region() - register a range of char device numbers
     * @dev: output parameter for first assigned number
     * @baseminor: first of the requested range of minor numbers
     * @count: the number of minor numbers required
     * @name: the name of the associated device or driver
     *
     * Allocates a range of char device numbers.  The major number will be
     * chosen dynamically, and returned (along with the first minor number)
     * in @dev.  Returns zero or a negative error code.
     */
    //int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,
    //                        const char *name)

    ret = alloc_chrdev_region(&dev, strgen_minor, strgen_nr_devs, "strgen");
    if (ret < 0) {
        printk(KERN_WARNING "strgen: can't get major %d\n", strgen_major);
        return ret;
    }
    strgen_major = MAJOR(dev);
    
    /* 
	 * allocate the devices -- we can't have them static, as the number
	 * can be specified at load time
	 */
	strgen_devices = kmalloc(strgen_nr_devs * sizeof(struct strgen_dev), GFP_KERNEL);
	if (!strgen_devices) {
		ret = -ENOMEM;
		goto fail;  /* Make this more graceful */
	}

	memset(strgen_devices, 0, strgen_nr_devs * sizeof(struct strgen_dev));

    printk(KERN_INFO "strgen: major=%d, minor=%d\n", strgen_major, strgen_minor);

    /* Initialize only one device. */
    strgen_setup_cdev(strgen_devices);
	dev = MKDEV(strgen_major, strgen_minor + strgen_nr_devs);

	return 0;                   /* successful */

fail:
	strgen_cleanup_module();
	return ret;
}
 
static void __exit strgen_cleanup(void)
{
	printk(KERN_INFO "cleanup string gen\n");
    strgen_cleanup_module();
}

module_init(strgen_init); 
module_exit(strgen_cleanup);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("string Generator tool");
MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
