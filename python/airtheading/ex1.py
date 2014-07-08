import thread
import time

__author__ = 'airead'


def print_time(name, delay):
    count = 0
    while count < 5:
        time.sleep(delay)
        count += 1
        print '%s: %s' % (name, time.ctime(time.time()))

try:
    thread.start_new_thread(print_time, ('Thread-1', 2, ))
except:
    print 'Error: unable to start thread'

while True:
    pass