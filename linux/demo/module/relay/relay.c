/**
 * @file relay.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/06 11:06:20
 */

/*
 *  read-mod - module for read example
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Copyright (C) IBM Corporation, 2005
 *
 * 2005-August	Created by Tom Zanussi <zanussi@us.ibm.com>
 */
#include <linux/module.h>
#include <linux/relay.h>
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>

/* This app's relay channel/control files will appear in /debug/read */
#define APP_DIR "relay"

#define MAX_EVENT_SIZE 256

/* app data */
static struct rchan *chan;
static struct dentry *dir;
static size_t subbuf_size = 64; //262144;
static size_t n_subbufs = 10;
static size_t event_n = 20;
static size_t write_count;
static int suspended;

static struct task_struct *kthread_thread;
static struct completion done;

static inline int rand(void)
{
	int val;
	get_random_bytes(&val, sizeof(val));
	if (val < 0)
		val = -val;

	return val;
}

static inline int get_random_number(int max)
{
	int val = rand();
	return val / (INT_MAX / max + 1);
}

static int test_thread(void *unused)
{
	int i, rand_n, count;
	char buf[MAX_EVENT_SIZE + 1];
	
	allow_signal(SIGKILL);
	allow_signal(SIGTERM);

	msleep(1000);

	while (!signal_pending(current)) {
		rand_n = get_random_number(event_n);
		if (!rand_n)
			rand_n = 1;
		for (i = 0; i < rand_n; i++) {
			count = snprintf(buf, MAX_EVENT_SIZE,
					 "[%08lu]test event\n", write_count++);
			relay_write(chan, buf, count);
		}
		
		if (kthread_should_stop())
			break;
		msleep(1000);
	}

	complete(&done);

	while(!kthread_should_stop()) {
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	}
	
	return 0;
}

static void start_test_thread(void)
{
	int cpu = 0;
	struct task_struct *p;

	init_completion(&done);
	
	p = kthread_create(test_thread, NULL, "%s/%d", "test", cpu);
	if (IS_ERR(p))
		return;
	if (p) {
		kthread_bind(p, cpu);
		wake_up_process(p);
		kthread_thread = p;
	}
}

static void stop_test_thread(void)
{
	if (kthread_thread) {
		kthread_stop(kthread_thread);
		kthread_thread = NULL;
	}
}

/*
 * subbuf_start() relay callback.
 *
 * Defined so that we know when events are dropped due to the buffer-full
 * condition.
 */
static int subbuf_start_handler(struct rchan_buf *buf,
                                void *subbuf,
                                void *prev_subbuf,
                                size_t prev_padding)
{
	if (relay_buf_full(buf)) {
		if (!suspended) {
			suspended = 1;
			printk("cpu %d buffer full!!!\n", smp_processor_id());
		}
		return 0;
	} else if (suspended) {
		suspended = 0;
		printk("cpu %d buffer no longer full.\n", smp_processor_id());
	}

	return 1;
}

/*
 * file_create() callback.  Creates relay file in debugfs.
 */
static struct dentry *create_buf_file_handler(const char *filename,
					      struct dentry *parent,
					      int mode,
					      struct rchan_buf *buf,
					      int *is_global)
{
	struct dentry *buf_file;
	
	buf_file = debugfs_create_file(filename, mode, parent, buf,
				       &relay_file_operations);

	return buf_file;
}

/*
 * file_remove() default callback.  Removes relay file in debugfs.
 */
static int remove_buf_file_handler(struct dentry *dentry)
{
	debugfs_remove(dentry);

	return 0;
}

/*
 * relay callbacks
 */
static struct rchan_callbacks relay_callbacks =
{
	.subbuf_start = subbuf_start_handler,
	.create_buf_file = create_buf_file_handler,
	.remove_buf_file = remove_buf_file_handler,
};


/**
 *	create_channel - creates channel /debug/APP_DIR/cpuXXX
 *
 *	Creates channel along with associated produced/consumed control files
 *
 *	Returns channel on success, NULL otherwise
 */
static struct rchan *create_channel(unsigned size,
				    unsigned n)
{
	struct rchan *channel;
	
	channel = relay_open("relay", dir, size, n, &relay_callbacks, NULL);
	
	if (!channel) {
		printk("relay app channel creation failed\n");
		return NULL;
	}

	return channel;
}

/**
 *	destroy_channel - destroys channel /debug/APP_DIR/cpuXXX
 *
 *	Destroys channel along with associated produced/consumed control files
 */
static void destroy_channel(void)
{
	if (chan) {
		relay_close(chan);
		chan = NULL;
	}
}

/**
 *	module init - creates channel management control files
 *
 *	Returns 0 on success, negative otherwise.
 */
static int init(void)
{
	dir = debugfs_create_dir(APP_DIR, NULL);
	if (!dir) {
		printk("Couldn't create relay app directory.\n");
		return -ENOMEM;
	}

	chan = create_channel(subbuf_size, n_subbufs);
	if (!chan) {
		debugfs_remove(dir);
		return -ENOMEM;
	}

	start_test_thread();
	
	return 0;
}

	
static void cleanup(void)
{
	stop_test_thread();
	destroy_channel();
	if (dir)
		debugfs_remove(dir);
}

module_init(init);
module_exit(cleanup);
MODULE_LICENSE("GPL");
