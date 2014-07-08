from blinker import signal

__author__ = 'airead'

started = signal('round-started')


def each(r):
    print 'Round %s!' % r


started.connect(each)


def round_two(r):
    print 'This is round two'


started.connect(round_two, sender=2)

for r in range(1, 4):
    started.send(r)
