#!/usr/bin/env python 

import dbus 

bus=dbus.SystemBus()
bus_obj = bus.get_object('org.freedesktop.DBus', '/')
iface = dbus.Interface(bus_obj, 'org.freedesktop.DBus')
names=iface.ListActivatableNames() 
for n in names: print n
