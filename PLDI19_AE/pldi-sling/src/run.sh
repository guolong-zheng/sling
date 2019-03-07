#!/bin/bash

SIZE=$1
DEFN=$2
FILE=$3

# Compile
pushd $(dirname $FILE)
mkdir -p AEoutput
fname=${FILE%.c}
if [ ! -f $fname ]; then
    gcc $(basename $FILE) header.c -g -o $(basename $fname)
fi
popd

# Get interested locations
pre=$(grep -n -E  "//pre" $FILE | cut -d: -f1)
post=$(grep -n -E  "//post" $FILE | cut -d: -f1)
inv=$(grep -n -E  "//loop" $FILE | cut -d: -f1)

# Run SLING
python dynsl.py -input $fname -pre $pre -post $post -inv $inv -size $SIZE -def $DEFN | tee $(dirname $FILE)/AEoutput/$(basename $fname).txt
