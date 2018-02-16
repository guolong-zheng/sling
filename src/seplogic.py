from functools import partial
import copy

class VarUtil(object):
    fv_id = 0

    @classmethod
    def mk_fresh(self, v = ''):
        self.fv_id = self.fv_id + 1
        if v == '':
            nv = 'fv!'
        else:
            nv = v + '!'
        return nv + str(self.fv_id)

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
        trans_sst = getattr(self, '__subst__', self.generic_subst)
        return trans_sst(sst)

    def generic_subst(self, sst):
        clone = copy.copy(self)
        fields = clone.__dict__
        for fid in fields:
            val = fields[fid]
            if isinstance(val, SepLogic):
                setattr(clone, fid, val.subst(sst))
        return clone

class PExpr(SepLogic):
    pass

class HExpr(SepLogic):
    pass

class Null(HExpr):
    def __str__(self):
        return 'nil'

    def __fv__(self):
        return set()

class Var(PExpr, HExpr):
    def __init__(self, id, is_primed = False):
        self.id = id
        self.is_primed = is_primed

    def __str__(self):
        return (self.id + ('\'' if self.is_primed else ''))

    def __fv__(self):
        s = set()
        s.add(str(self))
        return s

    def __subst__(self, sst):
        v = str(self)
        if v in sst:
            return sst[v]
        return copy.copy(self)

class IConst(PExpr):
    def __init__(self, i):
        self.val = i

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
        else:
            raise SyntaxError("type inconsistency")

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

class PRel(SepLogic):
    pass

class BConst(PRel):
    def __init__(self, b):
        self.val = b

    def __str__(self):
        return str(self.val)

    def __fv__():
        return set()

class PBinRel(PRel):
    def __init__(self, left, op, right):
        self.op = RelOp.rel_op(op)
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

class PPred(PRel):
    def __init__(self, id, args):
        self.id = id
        self.args = args

    def __str__(self):
        return (self.id + '(' +
               ', '.join(map(str, self.args)) + ')')

    def __fv__(self):
        s = set()
        for arg in self.args:
            s.update(arg.fv())
        return s

class PNeg(PRel):
    def __init__(self, f):
        self.form = f

    def __str__(self):
        return 'not(' + str(self.form) + ')'

    def __fv__(self):
        return self.form.fv()

class PConj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + ' & ' + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

class PDisj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + ' | ' + str(self.right)

    def __fv__(self):
        return self.left.fv() | self.right.fv()

class PForall(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f

    def __str__(self):
        return ('(forall ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(vars)

    def __subst__(self, sst):
        for v in self.vars:
            if v in sst:
                del sst[v]
        return PForall(self.vars, self.form.subst(sst))

class PExists(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(self.vars)

    def __subst__(self, sst):
        for v in self.vars:
            if v in sst:
                del sst[v]
        return PExists(self.vars, self.form.subst(sst))

class HRel(SepLogic):
    pass

class HAtom(HRel):
    pass

class HEmp(HAtom):
    def __init__(self):
        pass

    def __str__(self):
        return 'emp'

    def __fv__():
        return set()

class HData(HAtom):
    def __init__(self, root, name, args):
        self.root = root
        self.name = name
        self.args = args

    def __str__(self):
        return (str(self.root) + '->' + self.name + '{' +
                (', '.join(map(str, self.args))) + '}')

    def __fv__():
        s = set()
        s.add(root)
        for arg in self.args:
            s.update(arg.fv())
        return s

class HPred(HAtom):
    def __init__(self, name, args):
        self.name = name
        self.args = args

    def __str__(self):
        return (self.name + '(' +
                (', '.join(map(str, self.args))) + ')')

    def __fv__():
        s = set()
        for arg in self.args:
            s.update(arg.fv())
        return s

class HStar(HRel):
    def __init__(self, left, right):
        if isinstance(left, HRel) and isinstance(right, HRel):
            self.left = left
            self.right = right
        else:
            raise SyntaxError('left or right is not a heap relation')

    def __str__(self):
        return (str(self.left) + ' * ' + str(self.right))

    def __fv__(self):
        return self.left.fv() | self.right.fv()

    def _partition(self, f):
        if isinstance(f, HData):
            return ([f], [])
        elif isinstance(f, HPred):
            return ([], [f])
        else:
            return f.partition()

    def partition(self):
        lds, lps = self._partition(self.left)
        rds, rps = self._partition(self.right)
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

    def __str__(self):
        return (str(self.heap) + ' & ' + str(self.pure))

    def __fv__(self):
        return self.heap.fv() | self.pure.fv()

    def is_emp(self):
        return isinstance(self.heap, HEmp)

class FExists(SH):
    def __init__(self, vars, f):
        if isinstance(f, SH):
            self.vars = vars
            self.form = f
        else:
            raise SyntaxError(str(f) + ' is not a symbolic-heap formula')

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

    def __fv__(self):
        return self.form.fv() - set(self.vars)

    def __subst__(self, sst):
        for v in self.vars:
            if v in sst:
                del sst[v]
        return PExists(self.vars, self.form.subst(sst))

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

class Prog(SepLogic):
    def __init__(self, data_defn_lst, pred_defn_lst):
        self.data_defn_lst = data_defn_lst
        self.pred_defn_lst = pred_defn_lst

    def __str__(self):
        return ('\n\n'.join(map(str, self.data_defn_lst + self.pred_defn_lst)))

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
