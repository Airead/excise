#!/bin/bash

PLAYER=mplayer
PROGRAM=$1
ADDR=

function help(){
    echo -e "programs: \n  ef915 hf887 nr905 hyhq"
}

case $PROGRAM in
    "ef915" ) # easy fm
	ADDR="mms://enmms.chinabroadcast.cn/fm91.5";;
    "hf887" ) # hit fm
	ADDR="mms://live.hitfm.cn/fm887";;
    "nr905" ) # cri news radio
	ADDR="mms://media.crinewsradio.cn/crinewsradio";;
    "hyhq" )
	ADDR="mms://live.cri.cn/hyhq";;
    *)
	ADDR="help";;
esac

if [ "$ADDR" = "help" ]; then
    help
else
    $PLAYER $ADDR
fi