#!/bin/bash
#
# Author: AireadFan <fgh1987168@gmail.com>
#
# sync dbus data to git-proj
#

DIR=glib

rsync -vcar  --include="*.c" --include="Makefile" --include="README" \
	--include="*.org" --include="*.sh" --include="demo" \
	--include="*.py" --include="*.xml" --include="$DIR" \
	--include="*.h" \
	--include="pygtk" --include="demo/sendstruct" \
        --exclude="*" \
	../$DIR/* ~/study/git-proj/excise/$DIR
