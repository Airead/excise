#!/usr/bin/env python

import socket
import sys

def send(ip, port, num):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error:
        print 'Failed to create socket'
        sys.exit()
    
    msg = "test"
    for i in range(num):
        try:
            s.sendto(msg, (ip, port))
        except socket.error, msg:
            print "Error " + str(msg[0]) + " Message " + msg[1]
            sys.exit()
    print "send", num, "packets"

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print sys.argv[0], '<ip> <port> <num>'
        sys.exit(0)
    elif sys.argv[1] == '-h':
        print sys.argv[0], '<ip> <port> <num>'
        sys.exit(0)
    else:
        dst_ip = sys.argv[1]
        dst_port = int(sys.argv[2])

    if len(sys.argv) == 4:
        num = int(sys.argv[3])
    else:
        num = 1;

    send(dst_ip, dst_port, num)