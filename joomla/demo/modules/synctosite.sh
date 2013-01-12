#!/bin/sh 

SERVER=/home/airead/study/nginx/html/site/modules/
SCRIPT=`readlink -f $0`
DIR=`dirname $SCRIPT`
CURDIR=`basename $DIR`
echo ================================
tput setaf 1
echo "$DIR ----------> $SERVER"
tput setaf 9
echo ================================

rsync -a --no-o -rv --rsh=ssh --exclude="utils/ipfrqs.conf" --exclude="*.log" --exclude="*.o" --exclude="*.ko" --exclude="*.cmd" --exclude="*~" --exclude="*.out" --exclude="*.symvers" --exclude="*.mod" --exclude="*.mod.c" --exclude="*.order" $DIR/* $SERVER
