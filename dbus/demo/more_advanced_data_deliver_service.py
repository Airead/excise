#!/usr/bin/env python

import gobject

import dbus
import dbus.service
import dbus.mainloop.glib

class AdvancedData(dbus.service.Object):
    def __init__(self, bus, object_path):
        dbus.service.Object.__init__(self, bus, object_path)
        self._last_input = None

    @dbus.service.method('airead.fan.MoreAdvancedDataType', in_signature='a(si)', out_signature='a(si)')
    def StructArrayPrint(self, struct_array):
        print "receive struct array:"
        for st in struct_array:
            for value in st:
                print value, ",",
            print '\n' + '-' * 28
        print '=' * 33
        ret = [('li', 21), ('wen', 22), ('feng', 23)]
        return ret

    @dbus.service.method('airead.fan.MoreAdvancedDataType', in_signature='a{sv}', out_signature='a{sv}')
    def DictDictPrint(self, dictdict):
        print "receive dict{sv}:"
        for subdict in dictdict:
            print "subdict:", subdict
            for key in dictdict[subdict]:
                print "    ", key, ":", dictdict[subdict][key]
            print '-' * 33
            
        print '=' * 33
        ret = {};
        ret['fanrenhao'] = {'name':'renhao', 'age':'24', 'gender': 'male'}
        ret['liwenfeng'] = {'name':'wenfeng', 'age':'22', 'gender': 'female'}
        return ret

    @dbus.service.method('airead.fan.MoreAdvancedDataType', in_signature='a(oa{sv})', out_signature='a(oa{sv})')
    def ObjectPathDictStructArrayPrint(self, complex_array):
        print "receive a(oa{sv}):"
        for struct in complex_array:
            for mem in struct:
                if type(mem) == dbus.Dictionary:
                    for key in mem:
                        print key, ":", mem[key]
                else:
                    print mem
            print '-' * 33
        print '=' * 33
        # o for objectpath
        o1 = dbus.ObjectPath("/path1")
        o2 = dbus.ObjectPath("/path2")
        # d for dictionary
        d1 = {'name':'renhao', 'age':24, 'gender': 'male'}
        d2 = {'name':'wenfeng', 'age':22, 'gender': 'female'}
        # s for struct
        s1 = (o1, d1)
        s2 = (o2, d2)
        ret = [s1, s2]
        return ret


if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

    session_bus = dbus.SessionBus()
    name = dbus.service.BusName("airead.fan.MoreAdvancedDataType", session_bus)
    object = AdvancedData(session_bus, '/airead/fan/MoreAdvancedDataType')

    mainloop = gobject.MainLoop()
    print "Running example service."
    mainloop.run()


