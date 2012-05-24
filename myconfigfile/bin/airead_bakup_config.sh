#!/bin/sh

# copy the config file to some directory

DIR=$1

sudo cp -r ~/bin $1/bin
sudo cp -r ~/.emacs $1
sudo cp -r ~/.emacs.d $1/.emacs.d
sudo mkdir -p $1/.config
sudo cp -r ~/.config/awesome $1/.config

