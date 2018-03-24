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

pre=$(grep -n -E  "//pre" $FILE | cut -d: -f1)
post=$(grep -n -E  "//post" $FILE | cut -d: -f1)

python dynsl.py -input $fname -pre $pre -post $post -size $SIZE -def $DEFN
