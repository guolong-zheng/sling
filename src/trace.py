import sys
sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os

class Field(object):
    pass

class PtrField(Field):
    def __init__(self, name, addr):
        self.name = name
        self.data = addr

    def __str__(self):
        return self.name + ':' + hex(self.data)

class DataField(Field):
    def __init__(self, name, data, raw_data):
        self.name = name
        self.data = data
        self.raw_data = raw_data

    def __str__(self):
        return self.name + ':' + str(self.data)

class Trace(object):
    pass

class HeapTrace(Trace):
    def __init__(self, addr, name, fields):
        self.addr = addr
        self.name = name
        self.fields = fields

    def __str__(self):
        return hex(self.addr) + ' -> ' + self.name + '{' + ('; '.join(map(str, self.fields))) + '}'

class StackTrace(Trace):
    def __init__(self, ptr, addr):
        self.ptr = ptr
        self.addr = addr

    def __str__(self):
        return self.ptr + ' = ' + hex(self.addr)
