#!/usr/bin/python

import gtk, sys

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Scale")
        self.set_size_request(260, 150)
        self.set_position(gtk.WIN_POS_CENTER)

        scale = gtk.HScale()
        scale.set_range(0, 100)
        scale.set_increments(1, 10)
        scale.set_digits(0)
        scale.set_size_request(160, 35)
        scale.connect("value-changed", self.on_changed)

        self.load_pixbufs()
        
        self.image = gtk.Image()
        self.image.set_from_pixbuf(self.mutp)

        
        fixed = gtk.Fixed()
        fixed.put(scale, 20, 40)
        fixed.put(self.image, 219, 50)

        self.add(fixed)

        self.connect("destroy", gtk.main_quit)
        self.show_all()

    def load_pixbufs(self):
        try:
            self.mutp = gtk.gdk.pixbuf_new_from_file("beizi.jpg")
            self.minp = gtk.gdk.pixbuf_new_from_file("xiaopohai.jpg")
            self.medp = gtk.gdk.pixbuf_new_from_file("gaoxiao.jpg")
            self.maxp = gtk.gdk.pixbuf_new_from_file("beizi.jpg")
        except Exception, e:
            print "Error reading Pixbufs"
            print e.message
            sys.exit(1)

    def on_changed(self, widget):
        val = widget.get_value()
        
        if val == 0:
            self.image.set_from_pixbuf(self.mutp)
        elif val > 0 and val <= 30:
            self.image.set_from_pixbuf(self.minp)
        elif val > 30 and val < 80:
            self.image.set_from_pixbuf(self.medp)
        else:
            self.image.set_from_pixbuf(self.maxp)

PyApp()
gtk.main()
