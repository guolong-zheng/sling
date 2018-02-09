from seplogic import *
from printer import *
import z3
import operator
import inspect

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

    def eval(self, e):
        method_name = 'eval_' + type(e).__name__
        evaluation = getattr(self, method_name, self.generic_eval)
        return evaluation(e)

    def generic_eval(self, e):
        raise Exception('No evaluation for ' + str(e) + ':' + type(e).__name__)

class Stack(Store):
    def __init__(self):
        Store.__init__(self)
        self.solver = z3.Solver()
        self.z3_symtab = {}

    def __str__(self):
        return self.__ho_str__(str)

    def eval_Var(self, e):
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

    def eval_IConst(self, e):
        return e.val

    def eval_BinOp(self, e):
        el = self.eval(e.left)
        er = self.eval(e.right)
        return ops[e.op](el, er)

    def eval_BConst(self, e):
        return e.val

    def eval_PBinRel(self, e):
        el = self.eval(e.left)
        er = self.eval(e.right)
        return ops[e.op](el, er)

    def eval_PNeg(self, e):
        ev = self.eval(e)
        return (not ev)

    def eval_PConj(self, e):
        el = self.eval(e.left)
        er = self.eval(e.right)
        return z3.And(el, er)

    def eval_PDisj(self, e):
        el = self.eval(e.left)
        er = self.eval(e.right)
        return z3.Or(el, er)

    def eval_PExists(self, e):
        bnd_vs = set(e.vars)
        stk_vs = set(self.store.keys())
        cls_vs = stk_vs & bnd_vs
        sst = {}
        for v in cls_vs:
            sst[v] = Var(VarUtil.mk_fresh(v))
        nbnd_vs = list(bnd_vs - stk_vs) + map(lambda v: v.id, sst.values())
        ne = PExists(nbnd_vs, e.form.subst(sst))
        print(ne.form)

        zvs = []
        for v in nbnd_vs:
            if v in self.z3_symtab:
                zvs.append(self.z3_symtab[v])
            else:
                zv = z3.Int(v)
                self.z3_symtab[v] = zv
                zvs.append(zv)
        f = self.eval(ne.form)
        ef = z3.Exists(zvs, f)
        print(ef)
        self.solver.add(ef)
        if self.solver.check() == z3.unsat:
            return False
        else:
            return True

class Heap(Store):
    def __str__(self):
        str_of_heap = (lambda (t, fs):
                       '(' + t + ')' + str_of_list(fs, str))
        return self.__ho_str__(str_of_heap)

class SHModel(object):
    pass

