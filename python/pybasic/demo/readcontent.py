#!/usr/bin/python

import sys

## file content
# 0 ppp1 221.217.8.158
# 0 ppp2 222.131.29.64

if (len(sys.argv) < 2):
    print "usage:", sys.argv[0], "<filename>"
    sys.exit(1)

filename = sys.argv[1]

FILE = open(filename, "r")
contents = FILE.readlines()
FILE.close()

print contents
lines = {}
for line in contents:
    line = line.split()
    if line != []:
        print line
        lines[line[1]] = line[0]
    #     data = line.split(':')[1].split()
    #     iface.readData(data)
    #     break;

print lines