#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Tooltips")
        self.set_size_request(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)
        
        self.connect("destroy", gtk.main_quit)
        
        self.fixed = gtk.Fixed()
        self.add(self.fixed)
        
        button = gtk.Button("Button")
        button.set_size_request(80, 35)
    
        self.fixed.put(button, 50, 50)

        self.set_tooltip_text("Window widget")
        button.set_tooltip_text("Button widget")

        self.show_all()

PyApp()
gtk.main()
