from debug import *
import seplogic as SL

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

    def __eq__(self, other):
        if isinstance(self, other.__class__):
            return self.__dict__ == other.__dict__
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

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

class TException(Exception):
    pass

class TInfer(object):
    def __init__(self):
        self.env = {}
        self.tmap = {}

    def create_TVar(self, v = None):
        ty = TVar()
        if v:
            self.env[v.id] = ty
        self.tmap[ty.id] = ty
        return ty

    def raise_type_error(self, f, current_typ, expected_typ):
        raise TException('Type mismatch on ' + str(f) + '\n' +
                         '  current type: ' + str(current_typ) + '\n' +
                         '  expected type: ' + str(expected_typ))

    #############################################################
    def infer(self, f):
        method_name = 'infer_' + type(f).__name__
        inference = getattr(self, method_name, self.generic_infer)
        return inference(f)

    def generic_infer(self, f):
        raise Exception('No type inference for ' +
                        type(f).__name__ + ':\n' + str(f))

    def infer_Prog(self, prog):
        for dd in prog.data_defn_lst:
            if dd.name not in self.env:
                self.env[dd.name] = TeData(dd.name, [])
            else:
                raise TException('The data node ' + dd.name +
                                 ' has duplicate definitions')

        for dd in prog.data_defn_lst:
            self.infer(dd)

        prog = prog.rename()
        debug(prog)

        for pred in prog.pred_defn_lst:
            if pred.name not in self.env:
                tparams = []
                for pp in pred.params:
                    ty = self.create_TVar(pp)
                    tparams.append(ty)
                self.env[pred.name] = TePred(pred.name, tparams)
            else:
                raise TException('The predicate ' + pred.name +
                                 ' has duplicate definitions')

        for pred in prog.pred_defn_lst:
            self.infer(pred)

        for v in self.env:
            ty = self.env[v]
            if isinstance(ty, TVar):
                self.env[v] = self.find_type(ty)

        prog = prog.type_annotate(self.env)
        debug(prog)
        return prog

    def infer_DataDef(self, dd):
        targs = []
        for fi in dd.fields:
            t = Type.typ(fi.typ)
            if not isinstance(t, PrimType) and fi.typ not in self.env:
                raise TException('Data type ' + fi.typ + ' is undeclared')
            else:
                targs.append((fi.name, t))
        # targs = map(lambda fi: (fi.name, Type.typ(fi.typ)), dd.fields)
        typ = TeData(dd.name, targs)
        self.env[dd.name] = typ

    def infer_PredDef(self, pred):
        for case in pred.cases:
            self.infer(case)

    def infer_FBase(self, f):
        self.unify(f.heap, TBool())
        self.unify(f.pure, TBool())

    def infer_FExists(self, f):
        for v in f.vars:
            ty = self.create_TVar(v)
        self.infer(f.form)

    #############################################################
    def unify(self, f, typ):
        method_name = 'unify_' + type(f).__name__
        unification = getattr(self, method_name, self.generic_unify)
        return unification(f, typ)

    def generic_unify(self, f, typ):
        raise Exception('No type unification for ' +
                        type(f).__name__ + ':\n' + str(f))

    def unify_HData(self, f, expected_typ):
        self.unify(f.root, TData(f.name))
        tdata = self.env[f.name]
        for arg, targ in zip(f.args, tdata.targs):
            _, ty = targ
            self.unify(arg, ty)

    def unify_HPred(self, f, expected_typ):
        tdata = self.env[f.name]
        for arg, tparam in zip(f.args, tdata.tparams):
            self.unify(arg, tparam)

    def unify_HEmp(self, f, expected_typ):
        pass

    def unify_HStar(self, f, expected_typ):
        self.unify(f.left, TBool())
        self.unify(f.right, TBool())

    def unify_PConj(self, f, expected_typ):
        self.unify(f.left, TBool())
        self.unify(f.right, TBool())

    def unify_PDisj(self, f, expected_typ):
        self.unify(f.left, TBool())
        self.unify(f.right, TBool())

    def unify_PNeg(self, f, expected_typ):
        self.unify(f.form, TBool())

    def unify_PExists(self, f):
        for v in f.vars:
            ty = self.create_TVar(v)
        self.unify(f.form, TBool())

    def unify_PForall(self, f):
        for v in f.vars:
            ty = self.create_TVar(v)
        self.unify(f.form, TBool())

    def unify_PBinRel(self, f, expected_typ):
        if f.op == SL.RelOp.EQ or f.op == SL.RelOp.NE:
            try:
                tyl = self.find_type(f.left)
                if isinstance(tyl, TVar):
                    tyr = self.find_type(f.right)
                    if isinstance(tyr, TVar):
                        ty = self.create_TVar()
                    else:
                        ty = tyr
                else:
                    ty = tyl
            except TException:
                ty = self.create_TVar()
        else:
            ty = TInt()
        self.unify(f.left, ty)
        self.unify(f.right,ty)

        for i in self.tmap:
            print i, self.tmap[i]

    def unify_BinOp(self, f, expected_typ):
        if isinstance(expected_typ, TVar):
            self.tmap[expected_typ.id] = TInt()
        elif isinstance(expected_typ, TInt):
            pass
        else:
            self.raise_type_error(f, TInt(), expected_typ)
        self.unify(f.left, TInt())
        self.unify(f.right, TInt())

    def unify_Var(self, f, expected_typ):
        current_typ = self.find_type(f)
        expected_typ = self.find_type(expected_typ)
        # debug(f.id + ': ' + str(current_typ) + ', ' + str(expected_typ))
        if isinstance(current_typ, TVar):
            self.env[f.id] = expected_typ
            self.tmap[current_typ.id] = expected_typ
        elif isinstance(expected_typ, TVar):
            self.tmap[expected_typ.id] = current_typ
        elif not (current_typ == expected_typ):
            self.raise_type_error(f, current_typ, expected_typ)
        else:
            pass

        for i in self.tmap:
            print(str(i) + ':' + str(self.tmap[i]))

    def unify_IConst(self, f, expected_typ):
        if isinstance(expected_typ, TVar):
            self.tmap[expected_typ.id] = TInt()
        elif not isinstance(expected_typ, TInt):
            self.raise_type_error(f, TInt(), expected_typ)

    def unify_BConst(self, f, expected_typ):
        if isinstance(expected_typ, TVar):
            self.tmap[expected_typ.id] = TBool()
        elif not isinstance(expected_typ, TBool):
            self.raise_type_error(f, TBool(), expected_typ)

    #############################################################
    def find_type(self, e):
        method_name = 'find_type_' + type(e).__name__
        finder = getattr(self, method_name, self.generic_find_type)
        return finder(e)

    def generic_find_type(self, e):
        if isinstance(e, Type):
            return e
        raise Exception('No type finder for ' +
                        type(e).__name__ + ':\n' + str(e))

    def find_type_TVar(self, ty):
        while isinstance(ty, TVar):
            oty = ty
            ty = self.tmap[ty.id]
            if isinstance(ty, TVar) and oty.id >= ty.id:
                break
        return ty

    def find_type_Var(self, e):
        try:
            ty = self.env[e.id]
            return self.find_type(ty)
        except:
            raise TException(e.id + ' is unbounded')

    def find_type_IConst(self, e):
        return TInt()

    #############################################################

