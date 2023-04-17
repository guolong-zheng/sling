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

from inspect import getframeinfo, stack
from printer import *
import ntpath
import sys

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def debug(obj):
    message = Printer.str_of(obj)
    caller = getframeinfo(stack()[1][0])
    print "%s:%d - %s" % (path_leaf(caller.filename),
                          caller.lineno,
                          message)
    sys.stdout.flush()
