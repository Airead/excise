#!/usr/bin/python

import sys
import time

if (len(sys.argv) < 3):
    print "usage:", sys.argv[0], "<iface_default> <iface_bypass> "
    sys.exit(1)

ifd = sys.argv[1]
ifb = sys.argv[2]

filename = "/proc/net/dev"


default_rx = [1,1]
default_tx = [1,1]
bypass_rx = [1,1]
bypass_tx = [1,1]

def format_num(num):
    suffix = ['B', 'K', 'M', 'G'];
    count = 1;
    base = 1024;
    while num / pow(1024, count) >= 1:
        count += 1
    s = "%.2f%s" % ((num * 1.0 / pow(1024, count - 1)), suffix[count - 1])
    return s

while True:
    FILE = open(filename, 'r')
    
    for line in FILE.readlines():
        if line.find(ifd) >= 0:
            data = line.split(':')[1].split()
            default_rx[0] = data[0]
            default_tx[0] = data[8]
#            print "default:", default_rx, default_tx
        elif line.find(ifb) >= 0:
            data = line.split(':')[1].split()
            bypass_rx[0] = data[0]
            bypass_tx[0] = data[8]
#            print "bypass:", bypass_rx, bypass_tx
    
    brxflow = int(bypass_rx[0]) - int(bypass_rx[1])
    btxflow = int(bypass_tx[0]) - int(bypass_tx[1])
    drxflow = int(default_rx[0]) - int(default_rx[1])
    dtxflow = int(default_tx[0]) - int(default_tx[1])
    
    default_rx[1] = default_rx[0]
    default_tx[1] = default_tx[0]
    bypass_rx[1] = bypass_rx[0]
    bypass_tx[1] = bypass_tx[0]
    
    print "(brx, drx) = (%s, %s), (btx, dtx) = (%s, %s)" % (format_num(brxflow), format_num(drxflow), format_num(btxflow), format_num(dtxflow))
    print "percent: rx %.2f%%, tx %.2f%%" % ((brxflow * 100.0 / (brxflow + drxflow + 1)), (btxflow * 100.0 / (btxflow + dtxflow + 1)))
    FILE.close()
    time.sleep(1)
