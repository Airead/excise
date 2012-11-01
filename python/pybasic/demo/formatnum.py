#!/usr/bin/python

def format_num(num):
    suffix = ['B', 'K', 'M', 'G'];
    count = 1;
    base = 1024;
    while num / pow(1024, count) > 1:
        count += 1
    s = str(num / pow(1024, count - 1)) + suffix[count - 1]
    return s

if __name__ == "__main__":
    print format_num(800)
    print format_num(7 * 1034)
    print format_num(8 * 1124 * 1394)
    print format_num(9 * 1355 * 2356 * 1234)
