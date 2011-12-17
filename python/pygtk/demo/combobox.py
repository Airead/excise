#!/usr/bin/python

import gtk

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("ComboBox")
        self.set_default_size(250, 200)
        self.set_position(gtk.WIN_POS_CENTER)

        cb = gtk.combo_box_new_text()
        cb.connect("changed", self.on_changed)
        cb.append_text('Ubuntu')
        cb.append_text('Mandriva')
        cb.append_text('Redhat')
        cb.append_text('Gentoo')
        cb.append_text('Mint')

        fixed = gtk.Fixed()
        fixed.put(cb, 50, 30)

        self.label = gtk.Label("-")
        fixed.put(self.label, 50, 140)

        self.add(fixed)
        self.connect("destroy", gtk.main_quit)
        self.show_all()

    def on_changed(self, widget):
        self.label.set_label(widget.get_active_text())

PyApp()
gtk.main()
