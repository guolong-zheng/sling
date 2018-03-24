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
    def __init__(self, loc, stack, heap):
        self.loc = loc
        self.stack = stack
        self.heap = heap 

    def __str__(self):
        return ('\nloc ' + str(self.loc) + ':\n' +
                str(self.stack) + '\n\n' + str(self.heap))
