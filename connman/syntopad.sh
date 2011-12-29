#!/bin/bash
#
# Author: AireadFan <fgh1987168@gmail.com>
#
# sync dbus data to git-proj
#

rsync -vcar -e "ssh"  --include="*.c" --include="Makefile" --include="README" \
	--include="*.org" --include="*.sh" --include="demo" \
	--include="*.py" --include="*.xml" --include="python" \
	--include="*.h" \
	--include="pygtk" --include="demo/sendstruct" \
        --exclude="*" \
	../connman/* ijimu@192.168.0.201:/home/ijimu/study/connman
