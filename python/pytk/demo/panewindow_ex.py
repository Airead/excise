#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk

root = Tk()

p = ttk.Panedwindow(root, orient=VERTICAL)
p.grid()
# first pane, which would get widgets gridded into it:
f1 = ttk.Labelframe(p, text='Pane1', width=100, height=100)
f2 = ttk.Labelframe(p, text='Pane2', width=100, height=100)  # second pane

f1 = ttk.Labelframe(p, width=100, height=100)
f2 = ttk.Labelframe(p, width=100, height=100)  # second pane

p.add(f1)
p.add(f2)

root.mainloop()
