#!/usr/bin/python

import dbus

bus = dbus.SystemBus()
obj = bus.get_object("net.connman", "/")
ifa = dbus.Interface(obj, "net.connman.Manager")
properties = ifa.GetProperties()

for key in properties:
    print key, '=', properties[key]

