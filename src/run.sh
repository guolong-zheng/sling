#!/bin/bash

FILE=$1
SIZE=$2
DEFN=$3
pushd $(dirname $FILE)
fname=${FILE%.c}
if [ ! -f $fname ]; then
    gcc $(basename $FILE) header.c -g -o $(basename $fname)
fi
popd

bps=$(grep -n -E  "//pre|//post" $FILE | cut -d: -f1)

python dynsl.py -input $fname -breaks $bps -size $SIZE -def $DEFN
