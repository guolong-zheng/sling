from seplogic import *
from trace import *
from typ import *
from printer import *
from debug import *
from utils import *
import z3
import operator
import itertools

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

    def __str__(self):
        return Printer.str_of(self.store)

    def add(self, v, val):
        self.store[v] = val

    def remove(self, v):
        if v in self.store:
            del self.store[v]

    def get(self, v):
        return self.store[v]

    def contains(self, v):
        return v in self.store

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

    def clone(self):
        stack = Stack()
        stack.store = self.store.copy()
        return stack

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

    # Translation to z3 formulas
    def trans_Var(self, e):
        try:
            return self.eval(e) # Return the stack value of e
        except:
             v = e.id
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

    def trans_PNeg(self, e):
        ev = self.eval(e.form, 'trans')
        return z3.Not(ev)

    def trans_PQuant(self, Quant, e):
        ne = e.rename()

        # Create z3's bounded variables
        zvs = []
        for v in ne.vars:
            vid = v.id
            if vid in self.z3_symtab:
                zvs.append(self.z3_symtab[vid])
            else:
                zv = z3.Int(vid)
                self.z3_symtab[vid] = zv
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
        # debug(ef)
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

    def is_unsat(self, e):
        return self.evaluate(e) == False

    def mk_ctx(self, ctx, cond):
        # nctx = []
        # for cx in ctx:
        #     cc = PConj(cx, cond)
        #     if not self.is_unsat(cc):
        #         nctx.append(cc)
        # return nctx
        return PConj(ctx, cond)

class Heap(Store):
    pass

class SHModel(object):
    def __init__(self, stack, heap, prog = None):
        self.stack = stack
        self.heap = heap
        self.prog = prog

    def __str__(self):
        sstack = str(self.stack)
        sheap = str(self.heap)
        return 'stack:\n' + sstack + '\n' + 'heap:\n' + sheap

    def add_prog(self, prog):
        self.prog = prog

    def clone(self):
        s = self.stack.clone()
        h = self.heap.clone()
        sh = SHModel(s, h)
        sh.add_prog(self.prog)
        return sh

    def satisfy(self, f):
        ctx = BConst(True)
        rctx = self._satisfy(ctx, f)
        debug(rctx)
        return rctx

    def _satisfy(self, ctx, f):
        method_name = '_satisfy_' + type(f).__name__
        checker = getattr(self, method_name, self.generic_satisfy)
        return checker(ctx, f)

    def generic_satisfy(self, ctx, f):
        raise Exception('No model checker for ' +
                        str(f) + ':' + type(f).__name__)

    def _satisfy_FBase(self, ctx, f):
        nctx = self.stack.mk_ctx(ctx, f.pure)
        rctx = self._satisfy(nctx, f.heap)
        return rctx

    def _satisfy_HEmp(self, ctx, f):
        return [(ctx, self)]

    def _satisfy_HData(self, ctx, f):
        s = self.stack
        h = self.heap
        if not h.dom():
            return []
        else:
            try:
                root = s.eval(f.root)
                (typ, fields) = h.get(root)
                if typ == f.name:
                    nh = h.clone()
                    ns = s.clone()
                    nh.remove(root)
                    field_vals = map(lambda f: f.data.val, fields)
                    # matches = map(lambda (a, v): PBinRel(a, '=', IConst(v)),
                    #               zip(f.args, field_vals))
                    mconds = []
                    for (a, v) in zip(f.args, field_vals):
                        mconds.append(PBinRel(a, '=', IConst(v)))
                        if (isinstance(a, Var) and
                            isinstance(a.typ, TData) and
                            not ns.contains(a.id)):
                            ns.add(a.id, Addr(v))
                    if mconds:
                        mcond = reduce(lambda m1, m2: PConj(m1, m2), mconds)
                        nctx = ns.mk_ctx(ctx, mcond)
                    else:
                        nctx = ctx
                    if ns.is_unsat(nctx):
                        return []
                    else:
                        nsh = SHModel(ns, nh)
                        nsh.add_prog(self.prog)
                        return [(nctx, nsh)]
                else: # The sorts are inconsistent
                    debug('HData: ' + f.root +
                          ' points to inconsistent data types' +
                          ' (' + typ + ', ' + f.name + ')')
                    return []
            except:
                debug('HData Cannot find the matched heap for HData ' + str(f))
                return []

    def _satisfy_HPred(self, ctx, f):
        pred_defn = self.prog.lookup(f.name)
        sst = VarUtil.mk_subst(pred_defn.params, f.args)
        sst_pred_defn = pred_defn.subst(sst)
        nctx = []
        for case in sst_pred_defn.cases:
            pcond = case.get_pure()
            pctx = self.stack.mk_ctx(ctx, pcond)
            if not self.stack.is_unsat(pctx):
                sh = self.clone()
                rctx = sh._satisfy(pctx, case.get_heap())
                nctx.extend(rctx)
        return nctx

    def _satisfy_HStar(self, ctx, f):
        hdata_lst, hpred_lst = f.heap_par()
        rctx = [(ctx, self)]
        for dp in (hdata_lst + hpred_lst):
            rcx = []
            for (cx, sh) in rctx:
                r = sh._satisfy(cx, dp)
                rcx.extend(r)
            rctx = rcx
        return rctx

    def _satisfy_FExists(self, ctx, f):
        heap_data_nodes, _ = f.heap_par()
        data_vars = map(lambda dn: dn.root.id, heap_data_nodes)
        exists_vars = f.vars
        exists_data_vars = filter(lambda v:
                                  isinstance(v.typ, TData) and
                                  v.id in data_vars and
                                  not self.stack.contains(v.id), exists_vars)
        rem_exists_vars = list(set(exists_vars) - set(exists_data_vars))

        stack_data_vars = filter(lambda v: v in self.stack.store, data_vars)
        stack_data_vars_dom = map(lambda v:
                                  self.stack.get(v).val, stack_data_vars)
        h_dom = self.heap.dom()
        exists_data_vars_dom = filter(lambda addr:
                                      addr not in stack_data_vars_dom, h_dom)
        exists_data_vars_dom_set = list(
            itertools.combinations_with_replacement(
                exists_data_vars_dom, len(exists_data_vars)))

        def process_dom(e_dom):
            e_mapping = zip(exists_data_vars, e_dom)
            e_sh = self.clone()
            for (v, addr) in e_mapping:
                e_sh.stack.add(v.id, Addr(addr))
            ectx = e_sh._satisfy(ctx, f.form)
            return ectx

        rctx = []
        for e_dom in exists_data_vars_dom_set:
            ectx = process_dom(e_dom)
            rctx.extend(ectx)

        # tasks = exists_data_vars_dom_set
        # def wp(tasks, Q):
        #     rs = [process_dom(e_dom) for e_dom in tasks]
        #     if Q is None:
        #         return rs
        #     else:
        #         Q.put(rs)
        # rctx = Utils.runMP("satisfy_PExists", tasks, wp, chunksiz = 1, doMP = True)

        return rctx

    def group_by(self, func, ls):
        grouped = {}
        for elem in ls:
            key = func(elem)
            grouped.setdefault(key, []).append(elem)
        return grouped


