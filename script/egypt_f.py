#!/usr/bin/python

# generate graph centered by function
# author: AireadFan
# mail: fgh1987168@gmail.com

import sys
import re
import sets

ilist = []                      # ilist for input list
olist = []                      # olist for output list
outset = sets.Set()                  # output sets

def get_couple(line):
    p = re.compile('"(.*)".*"(.*)".*')
    m = p.match(line)
    if m != None:
        c = (m.group(1), m.group(2))
        return c
    return None

def get_ilist(file):
    file_in = open(file, "r");

    for line in file_in.readlines():
        c = get_couple(line)
        if c != None:
            ilist.append(c)

# 1 for only before, 2 for only after
def get_olist(list, function, flag, before):
    before = before - 1;
    for l in list:
        if flag == 1:
            if l[1] == function:
                if before < 0:
                    return None
                if l not in outset:
                    outset.add(l)
                    get_olist(list, l[0], flag, before);
        else:
            if l[0] == function:
                if l not in outset:
                    outset.add(l)
                    get_olist(list, l[1], flag);
    return None
    
# ex for poweful
def get_olist_ex(list, function, before):
#    print list
    get_olist(list, function, 1, before)
#    get_olist(list, function, 2)

def main():
    if (len(sys.argv) < 4):
        print "usage:", sys.argv[0], "<dotfile> <func_name> <before>"
        sys.exit(1)
    
    dotfile = sys.argv[1]
    func_name = sys.argv[2]
    before = int(sys.argv[3])
    
    get_ilist(dotfile)
    
    get_olist_ex(ilist, func_name, before)

    print "digraph callgraph {"
    for s in outset:
        print '"' + s[0] + '" -> "' + s[1] + '" [style=solid];';
    print "}"

main()
