#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk

root = Tk()

frame = ttk.Frame(root)
frame.grid()

frame['width'] = 200
frame['height'] = 200

frame['padding'] = (5, 10)

frame['borderwidth'] = 2
frame['relief'] = 'sunken'

root.mainloop()
