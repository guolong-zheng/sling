class Field(object):
    pass

class PtrField(Field):
    def __init__(self, name, addr):
        self.name = name
        self.data = addr

    def __str__(self):
        return self.name + '=' + self.data

class DataField(Field):
    def __init__(self, name, data):
        self.name = name
        self.data = data

    def __str__(self):
        return self.name + '=' + self.data

class Trace(object):
    def __init__(self, root, fields):
        self.root = root
        self.fields = fields

    def __str__(self):
        return str(self.root) + '<' + (', '.join(map(str, self.fields))) + '>'
