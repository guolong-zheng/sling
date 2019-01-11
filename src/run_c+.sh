#!/bin/bash

FILE=$3
SIZE=$1
DEFN=$2
pushd $(dirname $FILE)
mkdir -p output
fname=${FILE%.cpp}
if [ ! -f $fname ]; then
#    g++ $(basename $FILE) header.c -g -o $(basename $fname)
     g++ $(basename $FILE) -g -o $(basename $fname)
fi
popd

pre=$(grep -n -E  "//pre" $FILE | cut -d: -f1)
post=$(grep -n -E  "//post" $FILE | cut -d: -f1)
inv=$(grep -n -E  "//loop" $FILE | cut -d: -f1)

python dynsl.py -input $fname -pre $pre -post $post -inv $inv -size $SIZE -def $DEFN | tee $(dirname $FILE)/output/$(basename $fname).txt
