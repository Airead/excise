#!/usr/bin/env python

# Head ends here

def doMoveh(dir):
    if dir < 0:
        return "LEFT"
    elif dir > 0:
        return "RIGHT"

def doMovev(dir):
    if dir < 0:
        return "UP"
    elif dir > 0:
        return "DOWN"

def getPrincessPos(n, grid):
    for i in range(n):
        for j in range(n):
            if grid[i][j] == 'p':
                return i,j

def nextMove(n,x,y,grid):
#    print n, x, y, grid
    px, py = getPrincessPos(n, grid)
#    print "princess is at", px, py
    movex = px - x
    movey = py - y
#    print "movexy is", movex, movey
    
    if movex != 0:
        ret = doMovev(movex)
    elif movey != 0:
        ret = doMoveh(movey)
    
    return ret
# Tail starts here
n = input()
x,y = [int(i) for i in raw_input().strip().split()]
grid = []
for i in xrange(0, n):
    grid.append(raw_input())

print nextMove(n,x,y,grid)