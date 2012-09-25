#include <linux/module.h>	
#include <linux/kernel.h>	
 
int hello_init_module(void)
{
	printk(KERN_INFO "init_module() called\n");
	return -2;
}
 
void hello_cleanup_module(void)
{
	printk(KERN_INFO "cleanup_module() called\n");
}

module_init(hello_init_module);
module_exit(hello_cleanup_module);
