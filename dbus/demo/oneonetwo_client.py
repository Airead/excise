#!/usr/bin/python

import sys
import dbus
from traceback import print_exc

def main():

    # get Session Bus
    bus = dbus.SessionBus()

    # get remote ojbect
    remote_object = bus.get_object("airead.fan.Example", "/airead/fan/Example")

    # get D-Bus Interface
    dbus_interface = dbus.Interface(remote_object, "airead.fan.Example")

    # call Example method
    ret = dbus_interface.Example(1, 1)
    print "result:", ret

main()
