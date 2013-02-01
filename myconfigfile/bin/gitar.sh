#!/bin/bash

if [ $# -lt 2 ]; then
    echo "usage: `basename $0` <prefix> <branch|tag>"
    exit 1
fi

PREFIX=$1
TAG=$2

git archive --prefix=$PREFIX-$TAG/ -o $PREFIX-$TAG.tar.gz $TAG
