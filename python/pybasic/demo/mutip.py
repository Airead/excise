#!/usr/bin/env python

import multiprocessing
import time

def func(msg):
    for i in xrange(3):
        print msg
        time.sleep(1)

if __name__ == '__main__':
    p = multiprocessing.Process(target=func, args=("hello", ))
    p.start()
    p.join()
    print "Sub-process done."