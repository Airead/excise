#!/usr/bin/python

import time
import pygame
from pygame.locals import *
from sys import exit
 
from random import *
from math import pi

class Postion:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Mass:
    def __init__(self, pos):
        self.pos = Postion(pos.x, pos.y)
        self.old = Postion(pos.x, pos.y)
        self.radius = 10
        self.friction = 0.2
        self.collide = True
        self.grav = True

    def draw(self, screen):
        pygame.draw.circle(screen, (255,0,0), (self.pos.x, self.pos.y), self.radius, 2);


def main():
    pygame.init()
    screen = pygame.display.set_mode((640, 480), 0, 32)
    pos = Postion(100, 200)
    mass = Mass(pos)
    mass.draw(screen)
    pygame.display.update()
    time.sleep(1)
    mass.pos.x = 300
    mass.draw(screen)
    pygame.display.update()
    time.sleep(1)
    

if __name__ == "__main__":
    main()
