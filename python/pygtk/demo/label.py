#!/usr/bin/python

import gtk

lyrics = """Meet you downstairs in the bar and heard
your rolled up sleeves and your skull t-shirt
You say why did you do it with him today?
and sniff me out like I was Tanqueray
cause you're my fella, my guy
hand me your stella and fly
by the time I'm out the door
you tear men down like Roger Moore
I cheated myself
like I knew I would
I told ya, I was trouble
you know that I'm no good"""

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_position(gtk.WIN_POS_CENTER)
        self.set_border_width(20)
        self.connect("destroy", gtk.main_quit)
        self.set_title("You know I'm no Good")

        label = gtk.Label(lyrics)
        self.add(label)
        self.show_all()

PyApp()
gtk.main()

