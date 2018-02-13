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

    def eval(self, e, func='eval'):
        method_name = func + '_' + type(e).__name__
        if not hasattr(self, method_name):
            method_name = 'eval_' + type(e).__name__
        default_eval = lambda func: lambda e: self.generic_eval(e, func)
        evaluation = getattr(self, method_name, default_eval(func))
        if method_name.startswith('eval'):
            return evaluation(e, func)
        else:
            return evaluation(e)

    def generic_eval(self, e, func):
        raise Exception('No evaluation ' + '(' + func + ') ' +
                        'for ' + str(e) + ':' + type(e).__name__)

class Stack(Store):
    def __init__(self):
        Store.__init__(self)
        self.solver = z3.Solver()
        self.solver.set("timeout", 500)
        self.z3_symtab = {}

    def __str__(self):
        return self.__ho_str__(str)

    # Evaluation expressions to values
    def eval_Var(self, e, func='eval'):
        return self.get(e.id).val

    def eval_IConst(self, e, func='eval'):
        return e.val

    def eval_BinOp(self, e, func='eval'):
        el = self.eval(e.left, func)
        er = self.eval(e.right, func)
        return ops[e.op](el, er)

    def eval_BConst(self, e, func='eval'):
        return e.val

    def eval_PBinRel(self, e, func='eval'):
        el = self.eval(e.left, func)
        er = self.eval(e.right, func)
        return ops[e.op](el, er)

    def eval_PNeg(self, e, func='eval'):
        ev = self.eval(e, func)
        return (not ev)

    # Translation to z3 formulas
    def trans_Var(self, e):
        try:
            return self.eval(e)
        except:
             v = str(e)
             if v in self.z3_symtab:
                 return self.z3_symtab[v]
             else:
                 zv = z3.Int(v)
                 self.z3_symtab[v] = zv
                 return zv

    def trans_PConj(self, e):
        el = self.eval(e.left, 'trans')
        er = self.eval(e.right, 'trans')
        return z3.And(el, er)

    def trans_PDisj(self, e):
        el = self.eval(e.left, 'trans')
        er = self.eval(e.right, 'trans')
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
        f = self.eval(ne.form, 'trans')
        if Quant == PExists:
            ef = z3.Exists(zvs, f)
        else:
            ef = z3.ForAll(zvs, f)
        return ef

    def trans_PExists(self, e):
        return self.trans_PQuant(PExists, e)

    def trans_PForall(self, e):
        return self.trans_PQuant(PForall, e)

    def evaluate(self, e):
        ef = self.eval(e, 'trans')
        debug(str(ef))
        self.solver.push()
        self.solver.add(ef)
        try:
            r = self.solver.check()
            if r == z3.unsat:
                return Ternary(False)
            elif r == z3.sat:
                # m = self.solver.model()
                return Ternary(True)
            else:
                return Ternary(None) # unknown
        except:
            return Ternary(None)
        finally:
            self.solver.pop()

class Heap(Store):
    def __str__(self):
        str_of_heap = (lambda (t, fs):
                       '(' + t + ')' + str_of_list(fs, str))
        return self.__ho_str__(str_of_heap)

class SHModel(object):
    def __init__(self, stack, heap):
        self.stack = stack
        self.heap = heap

    def satisfy(self, f):
        method_name = 'satisfy_' + type(f).__name__
        checker = getattr(self, method_name, self.generic_satisfy)
        return checker(f)

    def generic_satisfy(self, f):
        raise Exception('No model checker for ' +
                        str(f) + ':' + type(f).__name__)

    def satisfy_FBase(self, f):
        p = f.pure
        h = f.heap
        return (self.stack.eval(p) & self.satisfy(h))

    def satisfy_HEmp(self, f):
        dom_h = self.heap.dom()
        is_empty_dom = not(bool(dom_h))
        return Ternary(is_empty_dom)

    def satisfy_HData(self, f):
        dom_h = self.heap.dom()
        if len(dom_h) == 1:
            stk = self.stack
            root = stk.get(f.root)
            debug(str(root))
            return Ternary(False)
        else:
            return Ternary(False)

