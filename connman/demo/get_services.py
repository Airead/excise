#!/usr/bin/python

import dbus

bus = dbus.SystemBus()
obj = bus.get_object("net.connman", "/")
ifa = dbus.Interface(obj, "net.connman.Manager")
properties = ifa.GetProperties()

for path in properties["Services"]:
    service = dbus.Interface(bus.get_object("net.connman", path),
                             "net.connman.Service")
    service_properties = service.GetProperties()
