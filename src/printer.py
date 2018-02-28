class Printer(object):
    @classmethod
    def str_of(self, obj):
        method_name = 'str_of_' + type(obj).__name__
        gen_str = getattr(self, method_name, str)
        return gen_str(obj)

    @classmethod
    def str_of_list(self, obj):
        elems = map(lambda e: self.str_of(e), obj)
        if (any(hasattr(e, '__dict__') for e in obj) and
           any(len(e) > 80 for e in elems)):
            sep = ',\n\n'
        else:
            sep = ', '
        return '[' + (sep.join(elems)) + ']'

    @classmethod
    def str_of_tuple(self, obj):
        elems = map(lambda e: self.str_of(e), list(obj))
        return '(' + (', '.join(elems)) + ')'

    @classmethod
    def str_of_dict(self, obj):
        elems = []
        for k in obj:
            elems.append(self.str_of(k) + ': ' + self.str_of((obj[k])))
        return '{' + ('\n'.join(elems)) + '}'
