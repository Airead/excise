#!/usr/bin/env python

import sys
from pgmagick.api import Image

def print_all_property():
    origin_img = Image('test.jpg')
    print "%dx%d" % (origin_img.width, origin_img.height)


if __name__ == '__main__':
    print sys.version_info
    print_all_property()