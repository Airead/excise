#!/usr/bin/python

filename = "test.dat"

n = 0
namelist = []
while n < 5:
    name = raw_input("Enter a name:")
    if type(name) == type(""):
        namelist.append(name)
        n = n + 1
    else:
        break

FILE = open(filename, "w")

FILE.writelines(namelist)

for name in namelist:
    FILE.write(name)

FILE.close()

