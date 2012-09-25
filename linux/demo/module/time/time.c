/**
 * @file fs.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/09/20 16:02:43
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

static int time_init_module(void)
{
    struct timeval tv;
    struct tm tm;

    do_gettimeofday(&tv);
    pr_info("second: %ld\n", tv.tv_sec);
    time_to_tm(tv.tv_sec, 0, &tm);

    pr_info("year: %ld, month: %d, day: %d, hour: %d, minute: %d, second: %d\n",
            tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    return 0;
}

static void time_cleanup_module(void)
{
    return;
}


module_init(time_init_module);
module_exit(time_cleanup_module);

MODULE_AUTHOR("Airead Fan <fgh1987168@gmail.com>");
MODULE_DESCRIPTION("net_device view");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.00");

