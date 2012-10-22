#!/bin/sh

FILE=$@

git diff --color $FILE | less -R
