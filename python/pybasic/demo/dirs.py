#!/usr/bin/env python

import sys
import os

def get_dir_list(path):
    dirs = os.listdir(path)
    list = []
    for d in dirs:
        abspath = os.path.join(path, d)
        if os.path.isdir(abspath):
            list.append(abspath)
    return list


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "usage:", sys.argv[0], "<path>"
        sys.exit(1)
    
    path = sys.argv[1]
    print get_dir_list(path)