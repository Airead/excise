#!/bin/bash

echo "getopts example"
echo "before getopts: parameter num $#"
while getopts "a:bc" opt
do
    echo run $opt
    case $opt in
        a)
            echo $OPTARG
            echo $OPTIND;;
        b) echo "b $OPTIND";;
        c) echo "c $OPTIND";;
    esac
done
echo $OPTIND
shift $(($OPTIND - 1))
echo "after getopts and shift: parameter num $#"
echo $0
echo $*
