/**
 * @file fs.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/20 16:02:43
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include "ext4.h"

static int fs_init_module(void)
{
	struct file_system_type *p;
	struct super_block *sb;

    p = get_fs_type("ext4");
    if (p == NULL) {
        pr_info("can't found fs type\n");
        goto out;
    } else {
        pr_info("filesystem: %s\n", p->name);
    }

    list_for_each_entry(sb, &p->fs_supers, s_instances) {
        pr_info("sb->s_subtype: %s, s_options: %s, s_id: %s\n", 
                sb->s_subtype, sb->s_options, sb->s_id);
    }
out:
	return 0;
}

static void fs_cleanup_module(void)
{
    return;
}


module_init(fs_init_module);
module_exit(fs_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("fs view");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.00");

