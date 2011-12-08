#!/bin/bash
#
# Author: AireadFan <fgh1987168@gmail.com>
#
# sync dbus data to git-proj
#

rsync -vcar  --include="*.c" --include="Makefile" --include="README" \
	--include="*.org" --include="*.sh" --include="demo" --exclude="*" \
	../dbus/* ~/study/git-proj/excise/dbus
