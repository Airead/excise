#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

int proc_init_module(void)
{
    /* Set up the anchor point */
        
    struct task_struct *task = &init_task;
    
    /* Walk through the task list, until we hit the init_task again */do {

        printk( KERN_INFO "*** %s [%d] parent %s\n",

                task->comm, task->pid, task->parent->comm );

    } while ( (task = next_task(task)) != &init_task );

    return 0;

}

void proc_cleanup_module(void)
{
    return;
}


module_init(proc_init_module);
module_exit(proc_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("process view");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.00");

