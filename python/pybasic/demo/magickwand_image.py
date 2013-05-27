#!/usr/bin/env python

import sys
from magickwand.image import Image


def print_all_property():
    origin_img = Image('test.jpg')
    print origin_img.size


if __name__ == '__main__':
    print sys.version_info
    print_all_property()