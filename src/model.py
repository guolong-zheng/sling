from seplogic import *
from printer import *
from debug import *
import z3
import operator

ops = {
    ArithOp.ADD: operator.add,
    ArithOp.SUB: operator.sub,
    ArithOp.MUL: operator.mul,
    ArithOp.DIV: operator.truediv,
    RelOp.LT: operator.lt,
    RelOp.LE: operator.le,
    RelOp.GT: operator.gt,
    RelOp.GE: operator.ge,
    RelOp.EQ: operator.eq,
    RelOp.NE: operator.ne }

class Store(object):
    def __init__(self):
        self.store = {}

    def __ho_str__(self, f):
        s = ''
        for v in self.store:
            s += str(v) + ' = ' + f(self.store[v]) + '\n'
        return s

    def __str__(self):
        return str(self.store)

    def add(self, v, val):
        self.store[v] = val

    def remove(self, v):
        if v in self.store:
            del self.store[v]

    def get(self, v):
        return self.store[v]

    def clone(self):
        copy = Store()
        copy.store = self.store.copy()
        return copy

    def update(self, another_store):
        self.store.update(another_store.store)

    def dom(self):
        return self.store.keys()

    def disjoint(self, another_store):
        return all(elem not in self.store
                   for elem in another_store.dom())

    def union(self, another_store):
        if self.disjoint(another_store):
            us = self.clone()
            us.update(another_store)
            return us
        else:
            raise Exception('Two stores are not disjoint')

    def trans(self, e):
        method_name = 'trans_' + type(e).__name__
        translator = getattr(self, method_name, self.generic_trans)
        return translator(e)

    def generic_trans(self, e):
        raise Exception('No translator for ' + str(e) + ':' + type(e).__name__)

class Stack(Store):
    def __init__(self):
        Store.__init__(self)
        self.solver = z3.Solver()
        self.solver.set("timeout", 500)
        self.z3_symtab = {}

    def __str__(self):
        return self.__ho_str__(str)

    def trans_Var(self, e):
        try:
            return self.get(e.id).val
        except:
             v = str(e)
             if v in self.z3_symtab:
                 return self.z3_symtab[v]
             else:
                 zv = z3.Int(v)
                 self.z3_symtab[v] = zv
                 return zv

    def trans_IConst(self, e):
        return e.val

    def trans_BinOp(self, e):
        el = self.trans(e.left)
        er = self.trans(e.right)
        return ops[e.op](el, er)

    def trans_BConst(self, e):
        return e.val

    def trans_PBinRel(self, e):
        el = self.trans(e.left)
        er = self.trans(e.right)
        return ops[e.op](el, er)

    def trans_PNeg(self, e):
        ev = self.trans(e)
        return (not ev)

    def trans_PConj(self, e):
        el = self.trans(e.left)
        er = self.trans(e.right)
        return z3.And(el, er)

    def trans_PDisj(self, e):
        el = self.trans(e.left)
        er = self.trans(e.right)
        return z3.Or(el, er)

    def trans_PQuant(self, Quant, e):
        bnd_vs = set(e.vars)
        stk_vs = set(self.store.keys())
        # Set of clashing vars to be renamed
        cls_vs = stk_vs & bnd_vs
        sst = {}
        for v in cls_vs:
            sst[v] = Var(VarUtil.mk_fresh(v))
        nbnd_vs = list(bnd_vs - stk_vs) + map(lambda v: v.id, sst.values())
        ne = Quant(nbnd_vs, e.form.subst(sst))

        # Create z3's bounded variables
        zvs = []
        for v in nbnd_vs:
            if v in self.z3_symtab:
                zvs.append(self.z3_symtab[v])
            else:
                zv = z3.Int(v)
                self.z3_symtab[v] = zv
                zvs.append(zv)
        f = self.trans(ne.form)
        if Quant == PExists:
            ef = z3.Exists(zvs, f)
        else:
            ef = z3.ForAll(zvs, f)
        return ef

    def trans_PExists(self, e):
        return self.trans_PQuant(PExists, e)

    def trans_PForall(self, e):
        return self.trans_PQuant(PForall, e)

    def eval(self, e):
        ef = self.trans(e)
        debug(str(ef))
        self.solver.push()
        self.solver.add(ef)
        res = self.solver.check()
        # m = self.solver.model()
        self.solver.pop()
        if res == z3.unsat:
            return False
        else:
            # debug(str(m))
            return True

class Heap(Store):
    def __str__(self):
        str_of_heap = (lambda (t, fs):
                       '(' + t + ')' + str_of_list(fs, str))
        return self.__ho_str__(str_of_heap)

class SHModel(object):
    pass

