#!/usr/bin/python

import gtk

actreesses = [('jessica alba', 'pomona', '1981'),
              ('sigourney weaver', 'newyork', '1949'),
              ('angelina jolie', 'los angeles', '1975'),
              ('natalie portman', 'jerusalem', '1981'),
              ('rachel weiss', 'london', '1971'),
              ('scarlett johansson', 'new york', '1984')]

class PyApp(gtk.Window):
    def __init__(self):
        super(PyApp, self).__init__()
        
        self.set_size_request(350, 250)
        self.set_position(gtk.WIN_POS_CENTER)
        self.connect("destroy", gtk.main_quit)
        self.set_title("ListView")
        
        vbox = gtk.VBox(False, 8)

        sw = gtk.ScrolledWindow()
        sw.set_shadow_type(gtk.SHADOW_ETCHED_IN)
        sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)

        vbox.pack_start(sw, True, True, 0)

        store = self.create_model()

        treeView = gtk.TreeView(store)
        treeView.connect("row-activated", self.on_activated)
        treeView.set_rules_hint(True)
        sw.add(treeView)

        self.create_columns(treeView)
        self.statusbar = gtk.Statusbar()

        vbox.pack_start(self.statusbar, False, False, 0)

        self.add(vbox)
        self.show_all()

    def create_model(self):
        store = gtk.ListStore(str, str, str)

        for act in actreesses:
            store.append([act[0], act[1], act[2]])

        return store

    def create_columns(self, treeView):
        rendererText = gtk.CellRendererText()
        column = gtk.TreeViewColumn("Name", rendererText, text=0)
        column.set_sort_column_id(0)
        treeView.append_column(column)

        rendererTex = gtk.CellRendererText()
        column = gtk.TreeViewColumn("Place", rendererText, text=1)
        column.set_sort_column_id(1)
        treeView.append_column(column)

        redererText = gtk.CellRendererText()
        column = gtk.TreeViewColumn("Year", rendererText, text=2)
        column.set_sort_column_id(2)
        treeView.append_column(column)

    def on_activated(self, widget, row, col):
        model - widget.get_model()
        text = model[row][0] + ", " + model[row][1] + ", " + model[row][2]
        self.statusbar.push(0, text)

PyApp()
gtk.main()
