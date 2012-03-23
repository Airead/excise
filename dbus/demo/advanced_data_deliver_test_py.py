#!/usr/bin/python

import sys
import dbus
from traceback import print_exc

def main():

    bus = dbus.SessionBus()
            
    try:
        remote_object = bus.get_object("airead.fan.AdvancedDataType", "/airead/fan/AdvancedDataType")
        dbus_interface = dbus.Interface(remote_object, "airead.fan.AdvancedDataType")

        #test dictionary
        dic = {'a':'apple', 'b':'banana', 'c':'cherry'}
        ret = dbus_interface.DictPrint(dic)
        print ret
        print '=' * 33 + "\n"

        #test int array
        intarray = [1, 2, 3, 4, 5, 6]
        ret = dbus_interface.IntArrayPrint(intarray)
        print ret
        print '=' * 33 + "\n"

        #test struct
        struct = ("fan", 24, 70.5, False)
        ret = dbus_interface.StructPrint(struct)
        print ret
        print '=' * 33 + "\n"

        #test variant
        variant = dic
        ret = dbus_interface.VariantPrint(variant)
        print ret
        print '-' * 33 + "\n"
        
        variant = intarray
        ret = dbus_interface.VariantPrint(variant)
        print ret
        print '-' * 33 + "\n"

        variant = struct
        ret = dbus_interface.VariantPrint(variant)
        print ret
        print '-' * 33 + "\n"

    except dbus.DBusException:
        print_exc()
        sys.exit(1)

main()
