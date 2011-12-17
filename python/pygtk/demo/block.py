#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Blocking a callback")
        self.set_size_request(250, 180)
        self.set_position(gtk.WIN_POS_CENTER)

        fixed = gtk.Fixed()
        button = gtk.Button("Click")
        button.set_size_request(80, 35)
        self.id = button.connect("clicked", self.on_clicked)
        fixed.put(button, 30, 50)

        check = gtk.CheckButton("Connect")
        check.set_active(True)
        check.connect("clicked", self.toggle_blocking, button)
        fixed.put(check, 130, 50)

        self.connect("destroy", gtk.main_quit)
        self.add(fixed)
        self.show_all()

    def on_clicked(self, widget):
        print "clicked"

    def toggle_blocking(self, checkbox, button):
        if checkbox.get_active():
            button.handler_unblock(self.id)
        else:
            button.handler_block(self.id)

PyApp()
gtk.main()
        
