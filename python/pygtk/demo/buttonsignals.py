#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Signals")
        self.set_size_request(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect("destroy", gtk.main_quit)

        fixed = gtk.Fixed()

        self.quit = gtk.Button("Quit")

        self.quit.connect("pressed", self.on_pressed)
        self.quit.connect("released", self.on_released)
        self.quit.connect("clicked", self.on_clicked)

        self.quit.set_size_request(80, 35)

        fixed.put(self.quit, 50, 50)

        self.add(fixed)
        self.show_all()
        self.emit_signal()

    def emit_signal(self):
        event = gtk.gdk.Event(gtk.gdk.BUTTON_RELEASE)
        event.button = 1
        event.window = self.quit.window
        event.send_event = True

        self.quit.emit("button-release-event", event)

    def on_clicked(self, widget):
        print "clicked"

    def on_released(self, widget):
        print "released"

    def on_pressed(self, widget):
        print "pressed"

PyApp()
gtk.main()
