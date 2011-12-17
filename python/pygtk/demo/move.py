#!/usr/bin/python

import gtk
import gobject

class PyApp(gtk.Window):
    __gsignals__ = {
        "configure-event" : "override"
        }

    def __init__(self):
        super(PyApp, self).__init__()

        self.set_size_request(200, 150)
        self.set_position(gtk.WIN_POS_CENTER)

        self.connect("destroy", gtk.main_quit)

        self.show_all()

    def do_configure_event(self, event):
        title = "%s, %s" % (event.x, event.y)
        self.set_title(title)
        gtk.Window.do_configure_event(self, event)

PyApp()
gtk.main()
