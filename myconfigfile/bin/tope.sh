#!/bin/sh

top -p `pidof $1 | tr -s ' ' ','`
