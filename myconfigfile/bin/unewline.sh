#!/bin/bash

if [ $# -lt 1 ]; then
	echo "usage `basename $0` <file_name>"
	exit 1
fi

echo -En "$(< $1)" > $1
