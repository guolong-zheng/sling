from debug import *

class Type(object):
    tid = 0

    @classmethod
    def mk_fresh(self):
        self.tid = self.tid + 1
        return self.tid

    @classmethod
    def typ(self, s):
        if s == 'int':
            return TInt()
        elif s == 'bool':
            return TBool()
        else:
            return TData(s)

class PrimType(Type):
    pass

class TVar(Type):
    def __init__(self):
        self.id = self.mk_fresh()

    def __str__(self):
        return 'TVar(' + str(self.id) + ')'

class TInt(PrimType):
    def __str__(self):
        return 'TInt'

class TBool(PrimType):
    def __str__(self):
        return 'TBool'

class TData(Type):
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return 'TData(' + self.name + ')'

class TeData(Type):
    def __init__(self, name, targs):
        self.name = name
        self.targs = targs

    def __str__(self):
        args = ', '.join(s + ':' + str(t) for (s, t)  in self.targs)
        return (self.name + ':(' + args + ')')

class TePred(Type):
    def __init__(self, name, tparams):
        self.name = name
        self.tparams = tparams

    def __str__(self):
        params = ', '.join(str(t) for t  in self.tparams)
        return (self.name + ':(' + params + ')')

class TInfer(object):
    def __init__(self):
        self.env = {}

    def infer(self, f):
        method_name = 'infer_' + type(f).__name__
        inference = getattr(self, method_name, self.generic_infer)
        return inference(f)

    def generic_infer(self, f):
        raise Exception('No type inference for ' +
                        str(f) + ':' + type(f).__name__)

    def infer_Prog(self, prog):
        for dd in prog.data_defn_lst:
            if dd.name not in self.env:
                self.env[dd.name] = TeData(dd.name, [])
            else:
                raise Exception('The data node ' + dd.name +
                                ' has been defined before')

        for dd in prog.data_defn_lst:
            self.infer(dd)

        for pred in prog.pred_defn_lst:
            if pred.name not in self.env:
                tparams = []
                for pp in pred.params:
                    tp = TVar()
                    self.env[pp] = tp
                    tparams.append(tp)
                self.env[pred.name] = TePred(pred.name, tparams)
            else:
                raise Exception('The predicate ' + pred.name +
                                ' has been defined before')
        debug(self.env)
        return prog

    def infer_DataDef(self, dd):
        targs = []
        for fi in dd.fields:
            t = Type.typ(fi.typ)
            if not isinstance(t, PrimType) and fi.typ not in self.env:
                raise Exception('Data type ' + fi.typ + ' is undeclared')
            else:
                targs.append((fi.name, t))
        # targs = map(lambda fi: (fi.name, Type.typ(fi.typ)), dd.fields)
        typ = TeData(dd.name, targs)
        self.env[dd.name] = typ

