#!/usr/bin/env python

import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class AdvancedData(dbus.service.Object):
    def __init__(self, bus, object_path):
        dbus.service.Object.__init__(self, bus, object_path)
        self._last_input = None

    @dbus.service.method('airead.fan.AdvancedDataType', in_signature='ai', out_signature='ai')
    def IntArrayPrint(self, ai):
        print "receive int array:", ai
        for i in range(len(ai)):
            print ai[i],
            ai[i] = ai[i] + 1
        print '\n' + '=' * 33
        return ai

    @dbus.service.method('airead.fan.AdvancedDataType', out_signature='(sidb)')
    def StructPrint(self, struct):
        print "receive struct:", struct
        for value in struct:
            print value
        print '=' * 33
        return ('Li', 24, 55.1, False)

    @dbus.service.method('airead.fan.AdvancedDataType', in_signature='v', out_signature='v')
    def VariantPrint(self, variant):
        print "receive variant:", variant
        print '=' * 33
        return variant

    @dbus.service.method('airead.fan.AdvancedDataType', in_signature='a{ss}', out_signature='a{ss}')
    def DictPrint(self, dict):
        print "receive dict:", dict
        for k in dict:
            print "%s: %s" % (k, dict[k])
        print '=' * 33
        return {'fan': "male", 'li': "female"}


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("airead.fan.AdvancedDataType", session_bus)
    object = AdvancedData(session_bus, '/airead/fan/AdvancedDataType')

    mainloop = gobject.MainLoop()
    print "Running example service."
    mainloop.run()


