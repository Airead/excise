#!/usr/bin/python

import dbus

conn = dbus.SystemBus()
obj = conn.get_object("net.connman", "/")
ifa = dbus.Interface(obj, "net.connman.Manager")
properties = ifa.GetProperties();

print properties
