#!/usr/bin/env python3

from tkinter import *
from tkinter import ttk

root = Tk()


def hello():
    print('hello')

button = ttk.Button(root, text="Okey", command=hello)

image = PhotoImage(file='/tmp/test/t.gif')
button['image'] = image

button.grid()

root.mainloop()
