#!/bin/bash
#
# Author: AireadFan <fgh1987168@gmail.com>
#
# sync dbus data to git-proj
#

PROJ=connman

rsync -vcar  --include="*.c" --include="Makefile" --include="README" \
	--include="*.org" --include="*.sh" --include="demo" \
	--include="*.py" --include="simplestruct" \
	--include="demo/interface" --include="demo/sendstruct" \
        --exclude="*" \
	../$PROJ/* ~/study/git-proj/excise/$PROJ
