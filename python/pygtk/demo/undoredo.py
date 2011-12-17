#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Toolbar")
        self.set_size_request(350, 300)
        self.modify_bg(gtk.STATE_NORMAL, gtk.gdk.Color(6400, 6400, 6400))
        self.set_position(gtk.WIN_POS_CENTER)

        self.count = 2

        toolbar = gtk.Toolbar()
        toolbar.set_style(gtk.TOOLBAR_ICONS)
        
        self.undo = gtk.ToolButton(gtk.STOCK_UNDO)
        self.redo = gtk.ToolButton(gtk.STOCK_REDO)
        sep = gtk.SeparatorToolItem()
        quit = gtk.ToolButton(gtk.STOCK_QUIT)

        toolbar.insert(self.undo, 0)
        toolbar.insert(self.redo, 1)
        toolbar.insert(sep, 2)
        toolbar.insert(quit, 3)

        self.undo.connect("clicked", self.on_undo)
        self.redo.connect("clicked", self.on_redo)
        quit.connect("clicked", gtk.main_quit)

        vbox = gtk.VBox(False, 2)
        vbox.pack_start(toolbar, False, False, 0)

        self.add(vbox)

        self.connect("destroy", gtk.main_quit)
        self.show_all()

    def on_undo(self, widget):
        self.count = self.count - 1

        if self.count <= 0:
            self.undo.set_sensitive(False)
            self.redo.set_sensitive(True)

    def on_redo(self, widget):
        self.count = self.count + 1

        if self.count >= 5:
            self.redo.set_sensitive(False)
            self.undo.set_sensitive(True)

PyApp()
gtk.main()
