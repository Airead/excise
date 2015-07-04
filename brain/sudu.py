# -*- coding: utf-8 -*-
# import sys
# reload(sys)
# sys.setdefaultencoding('UTF-8')

import curses
import time
import click
import random


def show(win, msg):
    win.erase()
    win.addstr(0, 1, msg)
    win.refresh()


def get_msg(content, length):
    point = random.randint(0, len(content) - length)
    msg = list(content[point:point + length])
    random.shuffle(msg)
    return ''.join(msg)


def filter(content):
    remove_chars = ' —，。；！,“”、　？‘’!-：….*<>《》\n'
    for ch in remove_chars:
        content = content.replace(ch, '')
    return content


@click.command()
@click.argument('file_path')
@click.option('--interval', '-i', default=1.0)
@click.option('--length', '-l', default=5)
@click.option('--flash', is_flag=True, default=False)
def cli(file_path, interval, length, flash):
    stdscr = curses.initscr()

    curses.noecho()
    curses.nocbreak()
    curses.curs_set(0)

    x, y = 0, 0
    height, width = 50, 100
    win = curses.newwin(height, width, y, x)

    with open(file_path, 'r') as f:
        content = f.read()
    content = filter(content)
    # content = content.encode('utf-8')

    while True:
        msg = get_msg(content, length)
        show(win, msg)
        if flash:
            time.sleep(0.2)
            win.erase()
            win.refresh()
        time.sleep(interval)

    curses.endwin()


if __name__ == '__main__':
    cli()
