#!/usr/bin/env python

import sys

from traceback import print_exc

import dbus

def main():
    bus = dbus.SessionBus()

    d = {}
    d['type'] = 'wifi'
    d['mode'] = 'managed'
    d['ssid'] = 'ijimu'
    d['Passphrase'] = "ijimu.com"

    try:
        remote_object = bus.get_object("dict.sample", "/DictEcho")
        dbus_interface = dbus.Interface(remote_object, "dict.Sample")
        dbus_interface.DictPrint(d)

    except dbus.DBusException:
        print_exc()
        sys.exit(1)


if __name__ == '__main__':
    main()
