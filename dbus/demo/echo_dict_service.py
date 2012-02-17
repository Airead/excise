#!/usr/bin/env python

import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class DictEcho(dbus.service.Object):
    def __init__(self, bus, object_path):
        dbus.service.Object.__init__(self, bus, object_path)
        self._last_input = None

    @dbus.service.method('dict.Sample',
                         in_signature='a{sv}')
    def DictPrint(self, dict_message):
        print "=" * 33
        print dict_message

    @dbus.service.method('dict.Sample',
                         in_signature='a{ss}')
    def DictPrintStr(self, dict_message):
        print "=" * 33
        print dict_message
        

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("dict.sample", session_bus)
    object = DictEcho(session_bus, '/DictEcho')

    mainloop = gobject.MainLoop()
    print "Running example service."
    mainloop.run()


