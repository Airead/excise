#!/usr/bin/env python

import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class BasicData(dbus.service.Object):
    def __init__(self, bus, object_path):
        dbus.service.Object.__init__(self, bus, object_path)
        self._last_input = None

    @dbus.service.method('airead.fan.BasicDataType', in_signature='y', out_signature='y')
    def BytePrint(self, byte):
        print "receive byte:", byte
        return byte + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='b', out_signature='b')
    def BooleanPrint(self, boolean):
        print "receive boolean:", boolean
        return not boolean

    @dbus.service.method('airead.fan.BasicDataType', in_signature='n', out_signature='n')
    def Int16Print(self, int16):
        print "receive int16:", int16
        return int16 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='q', out_signature='q')
    def Uint16Print(self, uint16):
        print "receive uint16:", uint16
        return uint16 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='i', out_signature='i')
    def Int32Print(self, int32):
        print "receive int32:", int32
        return int32 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='u', out_signature='u')
    def Uint32Print(self, uint32):
        print "receive uint32:", uint32
        return uint32 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='x', out_signature='x')
    def Int64Print(self, int64):
        print "receive int64:", int64
        return int64 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='t', out_signature='t')
    def Uint64Print(self, uint64):
        print "receive uint64:", uint64
        return uint64 + 1

    @dbus.service.method('airead.fan.BasicDataType', in_signature='d', out_signature='d')
    def DoublePrint(self, double):
        print "receive double:", double
        return double + 1.5

    @dbus.service.method('airead.fan.BasicDataType', in_signature='s', out_signature='s')
    def StringPrint(self, string):
        print "receive string:", string
        return string + "echo"

    @dbus.service.method('airead.fan.BasicDataType', in_signature='o', out_signature='o')
    def ObjectpathPrint(self, objectpath):
        print "receive objectpath:", objectpath
        return dbus.ObjectPath(objectpath + "_return")

    @dbus.service.method('airead.fan.BasicDataType', in_signature='g', out_signature='g')
    def SignaturePrint(self, signature):
        print "receive signature:", signature
        return signature + "s"

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("airead.fan.BasicDataType", session_bus)
    object = BasicData(session_bus, '/airead/fan/BasicDataType')

    mainloop = gobject.MainLoop()
    print "Running example service."
    mainloop.run()
