#!/bin/sh

find . -name "*" | xargs grep -n --color=auto "$1"
