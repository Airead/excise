#!/usr/bin/env python 

import dbus 

bus=dbus.SessionBus()
bus_obj = bus.get_object('org.fmddlmyy.Test', '/TestObj')
iface = dbus.Interface(bus_obj, 'org.fmddlmyy.Test.Basic')
sum = iface.Add(100,999) 
print sum
