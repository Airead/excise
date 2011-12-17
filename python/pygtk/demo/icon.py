#!/usr/bin/python

import gtk, sys

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Icon")
        self.set_size_request(250, 150)
        self.set_position(gtk.WIN_POS_CENTER)

        try:
            self.set_icon_from_file("web.png")
        except Exception, e:
            print e.message
            sys.exit(1)

        self.connect("destroy", gtk.main_quit)
        self.show()

PyApp()
gtk.main()
