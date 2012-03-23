#!/usr/bin/python

import sys
import dbus
from traceback import print_exc

def main():

    bus = dbus.SessionBus()
            
    try:
        remote_object = bus.get_object("airead.fan.MoreAdvancedDataType", "/airead/fan/MoreAdvancedDataType")
        dbus_interface = dbus.Interface(remote_object, "airead.fan.MoreAdvancedDataType")

        #test a(si)
        astruct = [('apple', 1), ('banana', 2), ('cherry', 5)]
        ret = dbus_interface.StructArrayPrint(astruct)
        print "receive struct array:"
        for struct in ret:
            for value in struct:
                print value
            print '-' * 28
        print '=' * 33 + "\n"

        #test a{sv}
        dic = {}
        dic['fanrenhao'] = {'name':'renhao', 'age':'24', 'gender': 'male'}
        dic['liwenfeng'] = {'name':'wenfeng', 'age':'22', 'gender': 'female'}
        ret = dbus_interface.DictDictPrint(dic)
        print "receive dict{sv}:"
        for subdict in ret:
            print "subdict:", subdict
            for key in ret[subdict]:
                print "    ", key, ":", ret[subdict][key]
            print '-' * 33
        print '=' * 33 + "\n"

        #test a(oa{sv})
        # o for objectpath
        o1 = dbus.ObjectPath("/p1")
        o2 = dbus.ObjectPath("/p2")
        # d for dictionary
        d1 = {'a':'apple', 'b': 'banana'}
        d2 = {'c': 'cherry', 'd': 88}
        complex_array = [(o1, d1), (o2, d2)]

        ret = dbus_interface.ObjectPathDictStructArrayPrint(complex_array)
        print "receive a(oa{sv}):"
        for struct in ret:
            for mem in struct:
                if type(mem) == dbus.Dictionary:
                    for key in mem:
                        print key, ":", mem[key]
                else:
                    print mem
            print '-' * 33
        print '=' * 33 + "\n"

    except dbus.DBusException:
        print_exc()
        sys.exit(1)

main()
