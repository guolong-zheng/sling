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

from utils import *

class Val(object):
    def __str__(self):
        return str(self.val)

class Int(Val):
    def __init__(self, val):
        self.val = int(val)

class Addr(Val):
    def __init__(self, addr):
        if addr == None:
            self.val = None
        elif isinstance(addr, basestring):
            if addr == "No value":
                self.val = None
            elif addr.startswith('0x'):
                self.val = int(addr, 16)
            else:
                self.val = int(addr)
        else:
            self.val = addr

class Field(object):
    pass

class PtrField(Field):
    def __init__(self, name, addr):
        self.name = name
        self.data = addr

    def __str__(self):
        return self.name + ':' + str(self.data)

class DataField(Field):
    def __init__(self, name, data):
        self.name = name
        self.data = data

    def __str__(self):
        return self.name + ':' + str(self.data)

class Trace(object):
    pass

class HeapTrace(Trace):
    def __init__(self, addr, typ, fields):
        self.addr = addr
        self.typ = typ
        self.fields = fields

    def __str__(self):
        return str(self.addr) + ' -> ' + self.typ + '{' + ('; '.join(map(str, self.fields))) + '}'

class StackTrace(Trace):
    def __init__(self, name, val):
        self.name = name
        self.val = val

    def __str__(self):
        return self.name + ' = ' + str(self.val)

class Traces(object):
    def __init__(self, loc, stack, heap, ret = None):
        self.id = Const.mk_fresh()
        self.loc = loc
        self.stack = stack
        self.heap = heap
        self.ret = ret

    def __str__(self):
        return ('\n' + str(self.id) + ' - ' + str(self.loc) + ':\n' +
                str(self.stack) + '\n\n' + str(self.heap) + '\n\n' +
                ('return: ' + str(self.ret) if self.ret else ''))

class TModel(object):
    def __init__(self, id, loc, stack, heap, ret, prog):
        import model
        self.id = id
        self.loc = loc
        self.sh = model.SHModel(stack, heap, prog)
        self.ret = ret

    def __str__(self):
        return ('\n' + str(self.loc) + ' - ' + str(self.id) + ':\n' +
                str(self.sh) + '\n\n' +
                ('return: ' + str(self.ret) if self.ret else ''))

    @classmethod
    def make(self, trace, prog):
        return TModel(trace.id, trace.loc,
                      trace.stack, trace.heap,
                      trace.ret, prog)

    @classmethod
    def make_lst(self, traces, prog):
        models = map(lambda trace: self.make(trace, prog), traces)
        return models




