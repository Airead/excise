#!/usr/bin/env python

import sys
import ping

def check_ping(hostname, count, timeout, packet_size=55):
    p = ping.Ping(hostname, timeout, packet_size)
    p.run(count)
    return p.send_count, p.receive_count, p.total_time

def main():
    if len(sys.argv) < 3:
        print("usage: %s <hostname> <count> [timeout] [packet_size]" % sys.argv[0])
        sys.exit(1)
    hostname = sys.argv[1]
    count = int(sys.argv[2])
    timeout = int(1000)
    packet_size = 55
    if len(sys.argv) > 4:
        timeout = int(sys.argv[3])
    if len(sys.argv) > 5:
        packet_size = int(sys.argv[4])

    sendCount, receiveCount, totalTime = check_ping(hostname, count, timeout, packet_size)
    print("sendCount %d, recevieCount %d, averageTime %.1f" % (sendCount, receiveCount, totalTime * 1.0 / receiveCount))

if __name__ == "__main__":
    main()