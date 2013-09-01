#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk

root = Tk()

l = ttk.Label(root, text="Full Name")
l.grid()

limage = ttk.Label(root, text="Hello World")
limage.grid()
image = PhotoImage(file='/tmp/test/t.gif')
limage['image'] = image

root.mainloop()
