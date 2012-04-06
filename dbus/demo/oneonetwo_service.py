#!/usr/bin/env python

import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class Example(dbus.service.Object):
    def __init__(self, bus, object_path):
        dbus.service.Object.__init__(self, bus, object_path)
        self._last_input = None

    @dbus.service.method('airead.fan.Example', in_signature='ii', out_signature='i')
    def Example(self, num1, num2):
        print "receive:", num1, num2
        return num1 + num2

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("airead.fan.Example", session_bus)
    object = Example(session_bus, '/airead/fan/Example')

    mainloop = gobject.MainLoop()
    print "Running example service."
    mainloop.run()


