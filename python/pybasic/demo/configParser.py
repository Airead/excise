#!/usr/bin/env python

import ConfigParser
import sys
import string

config = ConfigParser.ConfigParser()

# set a number of parameters
config.add_section("book")
config.set("book", "title", "the python beginner")
config.set("book", "author", "some one")

config.add_section("country")
config.set("country", "name", "China")

# write to screen
config.write(sys.stdout)

# write to file
configFile = open("/tmp/configParser.conf", "w+")
config.write(configFile)
configFile.close()

print "================================="
# read config file
rconfig = ConfigParser.ConfigParser()
rconfig.read("/tmp/configParser.conf")
print "author:", rconfig.get("book", "author")
print "country:", rconfig.get("country", "name")

# dump entire config file
for section in rconfig.sections():
    print section
    for option in rconfig.options(section):
        print "  ", option, "=", rconfig.get(section, option)
