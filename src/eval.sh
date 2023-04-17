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

dir=$1

for f in $dir/*.c;
    do
        echo "evaluating "$f
	./run_c.sh 10 $dir/defn.sl $f | tail -1 >> newexp.csv;
        echo "finished "$f
    done

echo "\n" >> newexp.csv
