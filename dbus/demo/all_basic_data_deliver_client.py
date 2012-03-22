#!/usr/bin/python

import sys
import dbus
from traceback import print_exc

def main():

    bus = dbus.SessionBus()
    method = sys.argv[1] + "Print"

    value = sys.argv[2]

    if sys.argv[1] == "Signature":
        value = dbus.Signature(value)
    elif sys.argv[1] == "Objectpath":
        value = dbus.ObjectPath(value)
    elif sys.argv[1] != "Byte" and sys.argv[1] != "Objectpath" and sys.argv[1] != "String":
        value = eval(value)
            
    try:
        remote_object = bus.get_object("airead.fan.BasicDataType", "/airead/fan/BasicDataType")
        dbus_interface = dbus.Interface(remote_object, "airead.fan.BasicDataType")
        method_call = dbus_interface.get_dbus_method(method);
        ret = method_call(value)
        print ret

    except dbus.DBusException:
        print_exc()
        sys.exit(1)


if __name__ == '__main__':
    if (len(sys.argv) < 3):
	print "Usage: %s <data_type> <data_value>" % (sys.argv[0])
	sys.exit(1)

main()
