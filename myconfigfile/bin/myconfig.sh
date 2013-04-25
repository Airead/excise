#!/bin/bash

sudo /home/airead/bin/off_vga.sh
xgamma -gamma 0.75
xmodmap -e "keycode 135 = Super_R"
sudo gnome-settings-daemon &
dropbox start
