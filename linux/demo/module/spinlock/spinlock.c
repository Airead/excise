#include <linux/init.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/list.h>

spinlock_t my_lock;

int spinlock_test( void )
{
    spin_lock_bh(&my_lock);
    spin_unlock_bh(&my_lock);

    return 0;
}

static int spinlocktest_init (void)
{
    spin_lock_init(&my_lock);
    spinlock_test();

    return -1;
}

static void spinlocktest_exit (void)
{
    return ;
}

module_init(spinlocktest_init);
module_exit(spinlocktest_exit);

MODULE_LICENSE("Dual BSD/GPL");
