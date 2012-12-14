#!/usr/bin/env python
#
# via:
#   http://stackoverflow.com/questions/36932/whats-the-best-way-to-implement-an-enum-in-python?page=1&tab=votes#tab-top
# Here's yet another way:
# 
# def enum(**enums):
#     return type('Enum', (), enums)
# Used like so:
# 
# >>> Numbers = enum(ONE=1, TWO=2, THREE='three')
# >>> Numbers.ONE
# 1
# >>> Numbers.TWO
# 2
# >>> Numbers.THREE
# 'three'
# You can also easily support automatic enumeration with something like this:
# 
# def enum(*sequential, **named):
#     enums = dict(zip(sequential, range(len(sequential))), **named)
#     return type('Enum', (), enums)
# Used like so:
# 
# >>> Numbers = enum('ZERO', 'ONE', 'TWO')
# >>> Numbers.ZERO
# 0
# >>> Numbers.ONE
# 1
# Support for converting the values back to names can be added this way:
# 
# def enum(*sequential, **named):
#     enums = dict(zip(sequential, range(len(sequential))), **named)
#     reverse = dict((value, key) for key, value in enums.iteritems())
#     enums['reverse_mapping'] = reverse
#     return type('Enum', (), enums)
# Obviously, this overwrites anything with that name, but it is useful for rendering your enums in output. It will throw KeyError if the reverse mapping doesn't exist. With the first example:
# 
# >>> Numbers.reverse_mapping['three']
# 'THREE'

def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    reverse = dict((value, key) for key, value in enums.iteritems())
    enums['length'] = len(enums)
    enums['reverse_mapping'] = reverse
    return type('Enum', (), enums)

Numbers = enum('ZERO', 'ONE', 'TWO', THREE='three', FOUR=8)
print Numbers.ZERO
print Numbers.ONE
print Numbers.reverse_mapping[2]
print Numbers.reverse_mapping['three']
print Numbers.FOUR
print Numbers.reverse_mapping[8]
print "length:", Numbers.length

if __name__ == "main":
    main()