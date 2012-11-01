/**
 * @file slab.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/26 14:14:01
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

struct test_t {
    int destip;
};

static struct kmem_cache *my_cachep;

static void remove_my_cache(void)
{
    if (my_cachep) kmem_cache_destroy( my_cachep );

    return;
}

int slab_test(int num)
{
    void *object;
    int i;

    pr_info( "Cache name is %s\n", my_cachep->name );
    pr_info( "Cache object size is %d\n", kmem_cache_size( my_cachep ) );

    for (i = 0; i < num; i++) {
        object = kmem_cache_alloc( my_cachep, GFP_KERNEL );
        if (object) {
            kmem_cache_free( my_cachep, object );
        }
    }

    return 0;
}

static int slabtest_init (void)
{
    my_cachep = KMEM_CACHE(test_t, SLAB_HWCACHE_ALIGN);
    
    slab_test(100);
    return 0;
}

static void slabtest_exit (void)
{
    remove_my_cache();

    return ;
}

module_init(slabtest_init);
module_exit(slabtest_exit);

MODULE_LICENSE("Dual BSD/GPL");
