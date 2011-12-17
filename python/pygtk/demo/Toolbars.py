#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Submenu")
        self.set_size_request(350, 300)
        self.modify_bg(gtk.STATE_NORMAL, gtk.gdk.Color(6400, 6400, 6400))
        self.set_position(gtk.WIN_POS_CENTER)

        upper = gtk.Toolbar()
        upper.set_style(gtk.TOOLBAR_ICONS)

        newtb = gtk.ToolButton(gtk.STOCK_NEW)
        opentb = gtk.ToolButton(gtk.STOCK_OPEN)
        savetb = gtk.ToolButton(gtk.STOCK_SAVE)

      
        upper.insert(newtb, 0)
        upper.insert(opentb, 1)
        upper.insert(savetb, 2)
    
        lower = gtk.Toolbar()
        lower.set_style(gtk.TOOLBAR_ICONS)

        quittb = gtk.ToolButton(gtk.STOCK_QUIT)
        quittb.connect("clicked", gtk.main_quit)
        lower.insert(quittb, 0)

        vbox = gtk.VBox(False, 0)
        vbox.pack_start(upper, False, False, 0)
        vbox.pack_start(lower, False, False, 0)

        self.add(vbox)

        self.connect("destroy", gtk.main_quit)
        self.show_all()

PyApp()
gtk.main()
        
