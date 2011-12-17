#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Quit Button")
        self.set_size_request(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect("destroy", self.on_destroy)

        fixed = gtk.Fixed()

        quit = gtk.Button("Quit")
        quit.connect("clicked", self.on_clicked)
        quit.set_size_request(80, 35)

        fixed.put(quit, 50, 50)

        self.add(fixed)
        self.show_all()

    def on_destroy(self, widget):
        gtk.main_quit()

    def on_clicked(self, widget):
        gtk.main_quit()

PyApp()
gtk.main()
