#!/usr/bin/python

import gtk
import sys

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()
        
        self.set_title("Fixed")
        self.set_size_request(300, 280)
        self.modify_bg(gtk.STATE_NORMAL, gtk.gdk.Color(6400, 6400, 6400))
        self.set_position(gtk.WIN_POS_CENTER)

        try:
            self.beizi = gtk.gdk.pixbuf_new_from_file("beizi.jpg")
            self.gaoxiao = gtk.gdk.pixbuf_new_from_file("gaoxiao.jpg")
            self.xiaopohai = gtk.gdk.pixbuf_new_from_file("xiaopohai.jpg")
        except Exception, e:
            print e.message
            sys.exit(1)

        image1 = gtk.Image()
        image2 = gtk.Image()
        image3 = gtk.Image()

        image1.set_from_pixbuf(self.beizi)
        image2.set_from_pixbuf(self.gaoxiao)
        image3.set_from_pixbuf(self.xiaopohai)

        fix = gtk.Fixed()

        fix.put(image1, 20, 20)
        fix.put(image2, 40, 160)
        fix.put(image3, 170, 50)

        self.add(fix)

        self.connect("destroy", gtk.main_quit)
        self.show_all()

PyApp()
gtk.main()
            
