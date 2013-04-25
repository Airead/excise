#!/usr/bin/env python

import sys

def doMoveh(dir):
    if dir < 0:
        print "LEFT"
        dir = dir + 1
    elif dir > 0:
        print "RIGHT"
        dir = dir - 1
    return dir

def doMovev(dir):
    if dir < 0:
        print "UP"
        dir = dir + 1
    elif dir > 0:
        print "DOWN"
        dir = dir - 1
    return dir

def getPrincessPos(n, grid):
    for i in range(n):
        for j in range(n):
            if grid[i][j] == 'p':
                return i,j

def displayPathtoPrincess(n,grid):
    bposv = bposh = n / 2
    # print "bot is at", bposx, bposy
    pposv, pposh = getPrincessPos(n, grid)
    # print "princess is at", pposv, pposh
    movev = pposv - bposv;
    moveh = pposh - bposh;

    # print "move steps", movev, moveh
    
    while movev != 0:
        movev = doMovev(movev)
    while moveh != 0:
        moveh = doMoveh(moveh)
#print all the moves here
# Tail starts here

if __name__ == "__main__":
    grid = []
    size = int(sys.stdin.readline())
    for i in range(size):
        line = sys.stdin.readline()
        line = line[:-1]
        grid.append(line)

    print grid

    displayPathtoPrincess(size, grid)