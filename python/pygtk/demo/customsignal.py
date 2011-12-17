#!/usr/bin/python

import gobject

class Sender(gobject.GObject):
    def __init__(self):
        self.__gobject_init__()

gobject.type_register(Sender)
gobject.signal_new("z_signal", Sender, gobject.SIGNAL_RUN_FIRST, gobject.TYPE_NONE, ())

class Receiver(gobject.GObject):
    def __init__(self, sender):
        self.__gobject_init__()

        sender.connect('z_signal', self.report_signal)

    def report_signal(self, sender):
        print "Receiver reacts to z_signal"

def user_callback(object):
    print "user callback reacts to z_signal"

if __name__ == '__main__':
    
    sender = Sender()
    receiver = Receiver(sender)

    sender.connect("z_signal", user_callback)
    sender.emit("z_signal")
