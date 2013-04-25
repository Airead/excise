#!/bin/bash

WORKTMP=/tmp/w.tmp
REPOTMP=/tmp/r.tmp
MESGTMP=/tmp/m.tmp

cat str_find_diff.txt | grep Working | cut -d' ' -f2 > $WORKTMP
cat str_find_diff.txt | grep Repository | cut -d' ' -f2 > $REPOTMP
cat str_find_diff.txt | grep Repository | cut -d' ' -f3 > $MESGTMP

works=(`cat $WORKTMP`)
repos=(`cat $REPOTMP`)
mesgs=(`cat $MESGTMP`)
len=${#works[*]}

echo "works: ${works[*]}"
echo "repos: ${repos[*]}"
echo "mesgs: ${mesgs[*]}"
echo "array length: $len"

for (( i=0; i<$len; i++ ));
do
    echo "${works[$i]} ${repos[$i]} ${mesgs[$i]}"
done

