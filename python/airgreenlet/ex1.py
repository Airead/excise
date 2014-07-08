from greenlet import greenlet
import time

__author__ = 'airead'


def test1():
    print 12
    time.sleep(3)
    gr2.switch()
    print 34


def test2():
    print 56
    time.sleep(5)
    gr1.switch()
    print 78


gr1 = greenlet(test1)
gr2 = greenlet(test2)

while True:
    time.sleep(1)
    print 'sleep 1'
    gr1.switch()
