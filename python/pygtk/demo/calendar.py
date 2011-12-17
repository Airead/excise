#!/usr/bin/python

import gtk

#!/usr/bin/python

import gtk, sys

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()

        self.set_title("Calendar")
        self.set_size_request(300, 270)
        self.set_position(gtk.WIN_POS_CENTER)
        self.set_border_width(2)

        self.label = gtk.Label("...")

        calendar = gtk.Calendar()
        calendar.connect("day_selected", self.on_day_selected)

        
        fixed = gtk.Fixed()
        fixed.put(calendar, 20, 20)
        fixed.put(self.label, 40, 230)

        self.add(fixed)

        self.connect("destroy", gtk.main_quit)
        self.show_all()

    def on_day_selected(self, widget):
        (year, month, day) = widget.get_date()
        self.label.set_label(str(year) + '/' + str(month) + '/' + str(day))

PyApp()
gtk.main()

