# -*- coding: utf-8 -*-
#
# created: Sat Dec  7 10:38:51 2013
#
import sys
import socket

__author__ = 'Airead Fan'


def resolve(hostname):
    return socket.gethostbyname(hostname)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print 'usage: %s <hostname>' % sys.argv[0]
        sys.exit(0)
    hostname = sys.argv[1]
    print resolve(hostname)
