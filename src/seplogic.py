from functools import partial
from typ import *
import copy
import ntpath
import settings

class VarUtil(object):
    fv_id = 0

    @classmethod
    def mk_fresh(self, v = None, typ = None):
        self.fv_id = self.fv_id + 1
        if not v:
            nid = 'fv!'
            ty = typ
        else:
            nid = v.id + '!'
            ty = v.typ
        return Var(nid + str(self.fv_id), typ = ty)

    @classmethod
    def mk_pred_param(self, v, pname):
        return Var(v.id + '!' + pname)

    @classmethod
    def mk_subst(self, ss, ds):
        sss = map(lambda v: v.id, ss)
        return dict(zip(sss, ds))

class ArithOp:
    ADD = '+'
    SUB = '-'
    MUL = '*'
    DIV = '/'

    @classmethod
    def arith_op(self, s):
        if s == '+':
            return self.ADD
        elif s == '-':
            return self.SUB
        elif s == '*':
            return self.MUL
        elif s == '/':
            return self.DIV
        else:
            raise SyntaxError('Unexpected arithmetic operator ' + s)

class RelOp:
    LT = '<'
    LE = '<='
    GT = '>'
    GE = '>='
    EQ = '='
    NE = '!='

    @classmethod
    def rel_op(self, s):
        if s == '<':
            return self.LT
        elif s == '<=':
            return self.LE
        elif s == '>':
            return self.GT
        elif s == '>=':
            return self.GE
        elif s == '=':
            return self.EQ
        elif s == '!=':
            return self.NE
        else:
            raise SyntaxError('Unexpected relational operator ' + s)

class SepLogic(object):
    def fv(self):
        return self.__fv__()

    def subst(self, sst):
        generic_subst = lambda sst: self.generic_clone('subst', [sst])
        trans_sst = getattr(self, '__subst__', generic_subst)
        return trans_sst(sst)

    def rename(self):
        renaming = getattr(self, '__rename__', self.generic_rename)
        return renaming()

    def generic_rename(self):
        return self.generic_clone('rename', [])

    def heap_par(self):
        partition = getattr(self, '__heap_par__', self.generic_heap_par)
        return partition()

    def generic_heap_par(self):
        # raise Exception('No heap partition for ' + type(self).__name__)
        return ([], [])

    def type_annotate(self, tab):
        generic_annotate = lambda tab: self.generic_clone('type_annotate', [tab])
        annotation = getattr(self, '__type_annotate__', generic_annotate)
        return annotation(tab)

    def __subst_Quant__(self, Quant, sst):
        for v in self.vars:
            if v.id in sst:
                del sst[v.id]
        ns = self.rename()
        ns.form = ns.form.subst(sst)
        return ns

    def __rename_Quant__(self, Quant):
        fvars = map(lambda v: VarUtil.mk_fresh(v), self.vars)
        sst = VarUtil.mk_subst(self.vars, fvars)
        nform = self.form.subst(sst)
        return Quant(fvars, nform.rename())

    def generic_clone(self, trans, args):
        clone = copy.copy(self)
        fields = clone.__dict__
        for fid in fields:
            val = fields[fid]
            if isinstance(val, SepLogic):
                func = getattr(val, trans)
                setattr(clone, fid, func(*args))
            if isinstance(val, list):
                cval = []
                for v in val:
                    def generic_func(*args):
                        return v
                    func = getattr(v, trans, generic_func)
                    cv = func(*args)
                    cval.append(cv)
                setattr(clone, fid, cval)
        return clone

    def mk_conj(self, f):
        combination = getattr(self, '__mk_conj__', self.generic_mk_conj)
        return combination(f)

    def generic_mk_conj(self, f):
        raise Exception('No combination for ' + type(self).__name__)
    
    def stat_atomic_preds(self):
        try:
            data_lst, pred_lst = self.__heap_par__()
            return len(data_lst), len(pred_lst)
        except:
            return 0, 0

class PExpr(SepLogic):
    pass

class HExpr(SepLogic):
    pass

class Null(HExpr):
    def __init__(self):
        self.typ = TData('nil')

    def __str__(self):
        return 'nil'

    def __fv__(self):
        return set()

    def __eq__(self, other):
        return isinstance(other, Null)

    def __ne__(self, other):
        return not isinstance(other, Null)

    def __hash__(self):
        return hash(self.__str__())

class Var(PExpr, HExpr):
    def __init__(self, id, is_primed = False, typ = None):
        self.id = id
        self.is_primed = is_primed
        self.typ = typ

    def __str__(self):
        id = self.id
        # try:
        #     i = id.index('!')
        #     id = id[:i]
        # except:
        #     pass
        if settings.print_type:
            typ = (':' + str(self.typ)) if self.typ else ''
        else:
            typ = ''
        return (id + ('\'' if self.is_primed else '') + typ)

    def __eq__(self, other):
        if isinstance(other, Var):
            return self.id == other.id
        else:
            return False

    def __ne__(self, other):
        return self.id != other.id

    def __hash__(self):
        return hash(self.__str__())

    def __fv__(self):
        s = set()
        s.add(self.id)
        return s

    def __subst__(self, sst):
        v = self.id
        if v in sst:
            return sst[v]
        return copy.copy(self)

    def __type_annotate__(self, tab):
        clone = copy.copy(self)
        if not clone.typ:
            clone.typ = tab[clone.id]
        return clone

class IConst(PExpr):
    def __init__(self, i):
        self.val = i
        self.typ = TInt()

    def __str__(self):
        return str(self.val)

    def __fv__(self):
        return set()

class BinOp(PExpr):
    def __init__(self, left, op, right):
        if isinstance(left, PExpr) and isinstance(right, PExpr):
            self.op = ArithOp.arith_op(op)
            self.left = left
            self.right = right
            self.typ = TInt()
        else:
            raise SyntaxError("type inconsistency")

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

class PRel(SepLogic):
    def __mk_conj__(self, f):
        if self == True:
            return f
        elif isinstance(f, PRel):
            if f == True:
                return self
            else:
                return PConj(self, f)
        elif isinstance(f, HRel):
            return FBase(f, self)
        elif isinstance(f, FBase):
            return FBase(f.heap, self.mk_conj(f.pure))
        elif isinstance(f, FExists):
            fvs = self.fv()
            if any(v.id in fvs for v in f.vars):
                nf = f.rename()
            else:
                nf = f
            return FExists(nf.vars, self.mk_conj(nf.form))
        else:
            raise Exception('No combination for ' + type(f).__name__)

class BConst(PRel):
    def __init__(self, b):
        self.val = b
        self.typ = TBool()

    def __str__(self):
        return str(self.val)

    def __fv__(self):
        return set()

    def __eq__(self, other):
       return (self.val is other.val if isinstance(other, BConst)
               else self.val is other)

    def __ne__(self, other):
       return not self == other

    def stat_pure_constrs(self):
        if self.val:
            return 0
        else:
            return 1

class PBinRel(PRel):
    def __init__(self, left, op, right):
        self.op = RelOp.rel_op(op)
        self.left = left
        self.right = right
        self.typ = TBool()

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

    def stat_pure_constrs(self):
        return 1

class PPred(PRel):
    def __init__(self, id, args):
        self.id = id
        self.args = args
        self.typ = TBool()

    def __str__(self):
        return (self.id + '(' +
               ', '.join(map(str, self.args)) + ')')

    def __fv__(self):
        s = set()
        for arg in self.args:
            s.update(arg.fv())
        return s

    def stat_pure_constrs(self):
        return 1

class PNeg(PRel):
    def __init__(self, f):
        self.form = f
        self.typ = TBool()

    def __str__(self):
        return 'not(' + str(self.form) + ')'

    def __fv__(self):
        return self.form.fv()

    def stat_pure_constrs(self):
        return self.form.stat_pure_constrs()

class PConj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right
        self.typ = TBool()

    def __str__(self):
        return str(self.left) + ' & ' + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

    def stat_pure_constrs(self):
        return self.left.stat_pure_constrs() + self.right.stat_pure_constrs()

class PDisj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right
        self.typ = TBool()

    def __str__(self):
        return str(self.left) + ' | ' + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

    def stat_pure_constrs(self):
        return self.left.stat_pure_constrs() + self.right.stat_pure_constrs()

class PForall(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f
        self.typ = TBool()

    def __str__(self):
        return ('(forall ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(vars)

    def __subst__(self, sst):
        return self.__subst_Quant__(PForall, sst)

    def __rename__(self):
        return self.__rename_Quant__(PForall)

    def stat_pure_constrs(self):
        return self.form.stat_pure_constrs()

class PExists(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f
        self.typ = TBool()

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(self.vars)

    def __subst__(self, sst):
        return self.__subst_Quant__(PExists, sst)

    def __rename__(self):
        return self.__rename_Quant__(PExists)

    def stat_pure_constrs(self):
        return self.form.stat_pure_constrs()

class HRel(SepLogic):
    def __mk_conj__(self, f):
        if isinstance(self, HEmp):
            return f
        elif isinstance(f, PRel):
            return FBase(self, f)
        elif isinstance(f, HRel):
            if isinstance(f, HEmp):
                return self
            else:
                return HStar(self, f)
        elif isinstance(f, FBase):
            return FBase(self.mk_conj(f.heap), f.pure)
        elif isinstance(f, FExists):
            fvs = self.fv()
            if any(v.id in fvs for v in f.vars):
                nf = f.rename()
            else:
                nf = f
            return FExists(nf.vars, self.mk_conj(nf.form))
        else:
            raise Exception('No combination for ' + type(f).__name__)

    def stat_pure_constrs(self):
        return 0

class HAtom(HRel):
    pass

class HEmp(HAtom):
    def __init__(self):
        self.typ = TBool()

    def __str__(self):
        return 'emp'

    def __fv__(self):
        return set()

class HData(HAtom):
    def __init__(self, root, name, args):
        self.root = root
        self.name = name
        self.args = args
        self.typ = TBool()

    def __str__(self):
        return (str(self.root) + '->' + self.name + '{' +
                (', '.join(map(str, self.args))) + '}')

    def __fv__(self):
        s = set()
        s.add(self.root.id)
        for arg in self.args:
            s.update(arg.fv())
        return s

    def __heap_par__(self):
        return ([self], [])

class HPred(HAtom):
    def __init__(self, name, args):
        self.name = name
        self.args = args
        self.typ = TBool()

    def __str__(self):
        return (self.name + '(' +
                (', '.join(map(str, self.args))) + ')')

    def __fv__(self):
        s = set()
        for arg in self.args:
            s.update(arg.fv())
        return s

    def __heap_par__(self):
        return ([], [self])

class HStar(HRel):
    def __init__(self, left, right):
        if isinstance(left, HRel) and isinstance(right, HRel):
            self.left = left
            self.right = right
            self.typ = TBool()
        else:
            raise SyntaxError('left or right is not a heap relation')

    def __str__(self):
        return (str(self.left) + ' * ' + str(self.right))

    def __fv__(self):
        return self.left.fv() | self.right.fv()

    def __heap_par__(self):
        lds, lps = self.left.heap_par()
        rds, rps = self.right.heap_par()
        lds.extend(rds)
        lps.extend(rps)
        return (lds, lps)

class SH(SepLogic):
    pass

class FBase(SH):
    def __init__(self, heap, pure):
        is_HRel = isinstance(heap, HRel)
        is_PRel = isinstance(pure, PRel)
        if not is_HRel:
            raise SyntaxError(str(heap) + ' is not a heap formula')
        elif not is_PRel:
            raise SyntaxError(str(pure) + ' is not a pure formula')
        else:
            self.heap = heap
            self.pure = pure
            self.typ = TBool()

    def __str__(self):
        return (str(self.heap) + ' & ' + str(self.pure))

    def __fv__(self):
        return self.heap.fv() | self.pure.fv()

    def __heap_par__(self):
        return self.heap.heap_par()

    def __mk_conj__(self, f):
        pf = self.pure.mk_conj(f)
        return self.heap.mk_conj(pf)

    def is_emp(self):
        return isinstance(self.heap, HEmp)

    def get_pure(self):
        return self.pure

    def get_heap(self):
        return self.heap

    def stat_pure_constrs(self):
        return self.pure.stat_pure_constrs()

class FExists(SH):
    def __init__(self, vars, f):
        self.vars = vars
        self.typ = TBool()
        if isinstance(f, SH):
            self.form = f
        elif isinstance(f, HRel):
            self.form = FBase(f, BConst(True))
        elif isinstance(f, PRel):
            self.form = FBase(HEmp(), f)
        else:
            raise SyntaxError(str(f) + ' is not a symbolic-heap formula')

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(map(lambda v: v.id, self.vars))

    def __heap_par__(self):
        return self.form.heap_par()

    def __subst__(self, sst):
        return self.__subst_Quant__(FExists, sst)

    def __rename__(self):
        return self.__rename_Quant__(FExists)

    def __mk_conj__(self, f):
        fvs = self.fv()
        if ((isinstance(f, FExists) or isinstance(f, PExists)) 
            and any(v.id in fvs for v in f.vars)):
            nself = self.rename()
        else:
            nself = self
        hpf = nself.form.mk_conj(f)
        if isinstance(hpf, FExists):
            return FExists(nself.vars + hpf.vars, hpf.form)
        else:
            return FExists(nself.vars, hpf)

    def get_pure(self):
        return self.form.get_pure()

    def get_heap(self):
        return FExists(self.vars, FBase(self.form.get_heap(), BConst(True)))

    def stat_pure_constrs(self):
        return self.form.stat_pure_constrs()

class DataDefField(SepLogic):
    def __init__(self, typ, name):
        self.typ = typ
        self.name = name

    def __str__(self):
        return (str(self.typ) + ' ' + self.name + ';')

class DataDef(SepLogic):
    def __init__(self, name, fields):
        self.name = name
        self.fields = fields

    def __str__(self):
        return ('data '+ self.name + ' {\n\t' +
                ('\n\t'.join(map(str, self.fields))) + '\n};')

class PredDef(SepLogic):
    def __init__(self, name, params, cases):
        self.name = name
        self.params = params
        self.cases = cases

    def __str__(self):
        return ('pred ' + self.name + '(' + (', '.join(map(str, self.params))) + ')' +
                ' := \n\t' + ('\n\t\/ '.join(map(str, self.cases))))

    def __rename__(self):
        fparams = map(lambda v: VarUtil.mk_pred_param(v, self.name), self.params)
        sst = VarUtil.mk_subst(self.params, fparams)
        ncases = map(lambda case: case.subst(sst), self.cases)
        ncases = map(lambda case: case.rename(), ncases)
        return PredDef(self.name, fparams, ncases)

class Prog(SepLogic):
    def __init__(self, data_defn_lst, pred_defn_lst):
        self.data_defn_lst = data_defn_lst
        self.pred_defn_lst = pred_defn_lst
        self.store = {}
        for defn in (data_defn_lst + pred_defn_lst):
            self.store[defn.name] = defn

    def __str__(self):
        return ('\n\n'.join(map(str, self.data_defn_lst + self.pred_defn_lst)))

    def lookup(self, name):
        return self.store[name]

class Ternary(object):
    def __init__(self, value=None):
       if any(value is v for v in (True, False, None)):
          self.value = value
       else:
           raise ValueError("Ternary value must be True, False, or None")

    def __eq__(self, other):
       return (self.value is other.value if isinstance(other, Ternary)
               else self.value is other)

    def __ne__(self, other):
       return not self == other

    def __nonzero__(self):   # Python 3: __bool__()
       raise TypeError("Ternary object may not be used as a Boolean")

    def __str__(self):
        return str(self.value)

    def __repr__(self):
        return "Ternary(%s)" % self.value

    def __and__(self, x):
        if self == True:
            return x
        else:
            return self
