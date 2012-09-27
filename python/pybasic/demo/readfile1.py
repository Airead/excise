#!/usr/bin/python

import sys


if (len(sys.argv) < 2):
    print "usage:", sys.argv[0], "<filename>"
    sys.exit(1)

filename = sys.argv[1]

FILE = open(filename, "r")

buf = FILE.read()

print buf

FILE.close()

