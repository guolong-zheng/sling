# Copyright (C) 2018-2023 Ton Chanh Le

# SLING is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# SLING is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with SLING. If not, see <https://www.gnu.org/licenses/>.

#!/bin/bash

FILE=$3
SIZE=$1
DEFN=$2
pushd $(dirname $FILE)
mkdir -p output
fname=${FILE%.c}
if [ ! -f $fname ]; then
    gcc $(basename $FILE) header.c -g -o $(basename $fname)
    # g++ $(basename $FILE) -g -o $(basename $fname)
fi
popd

pre=$(grep -n -E  "//pre" $FILE | cut -d: -f1)
post=$(grep -n -E  "//post" $FILE | cut -d: -f1)
inv=$(grep -n -E  "//loop" $FILE | cut -d: -f1)


/usr/bin/python2.7 dynsl.py -input $fname -pre $pre -post $post -inv $inv -size $SIZE -def $DEFN | tee $(dirname $FILE)/output/$(basename $fname).txt
