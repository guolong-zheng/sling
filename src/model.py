from seplogic import *
from trace import *
from typ import *
from printer import *
from debug import *
from utils import *
import z3
import operator
import itertools
import settings

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
        return copy.deepcopy(self)

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

    ###############
    def __getitem__(self, name):
        return self.get(name)

    def __iter__(self):
        return iter(self.store)

    def keys(self):
        return self.dom()

    def items(self):
        return self.store.items()

    def values(self):
        return self.store.values()
    ###############

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
        self.z3_symtab = {}

    def __contains__(self, v):
        return self.contains(v)

    def clone(self):
        stack = Stack()
        stack.store = copy.copy(self.store)
        return stack

    # Evaluation expressions to values
    def eval_Var(self, e, func='eval'):
        return self.get(e.id).val

    def eval_IConst(self, e, func='eval'):
        return e.val

    def eval_Null(self, e, func='eval'):
        return Const.nil_addr

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
                if isinstance(e.typ, TBool):
                    zv = z3.Bool(v)
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
                if isinstance(e.typ, TBool):
                    zv = z3.Bool(v)
                else:
                    zv = z3.Int(v)
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
        return Z3().solve(ef)

    def is_unsat(self, e):
        return self.evaluate(e) == False

class Heap(Store):
    def to_list(self):
        traces = []
        for addr in self:
            ty, fis = self[addr]
            trace = HeapTrace(Addr(addr), ty, fis)
            traces.append(trace)
        return traces

class Context(object):
    def __init__(self, state, exists_vars = []):
        self.exists_vars = exists_vars
        self.state = state

    @classmethod
    def mk_init_context(self):
        return Context(BConst(True))

    def __str__(self):
        return Printer.str_of(self.exists_vars) + ':' + str(self.state)

    def mk_conj(self, f):
        conj_state = self.state.mk_conj(f)
        return Context(conj_state, self.exists_vars)

    def add_vars(self, vs):
        exists_vars = self.exists_vars + vs
        return Context(self.state, exists_vars)

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
        sh = SHModel(s, h, self.prog)
        return sh

    def satisfy(self, f):
        ctx = Context.mk_init_context()
        rctx = self._satisfy(ctx, f)
        debug(rctx)
        return bool(rctx)

    def classic_satisfy(self, f):
        ctx = Context.mk_init_context()
        rctx = self._satisfy(ctx, f)
        # debug(rctx)
        res = any(not bool(sh.heap.dom()) for (ctx, sh) in rctx)
        return res

    def get_classic_ctx(self, f):
        ctx = Context.mk_init_context()
        rctx = self._satisfy(ctx, f)
        classic_rctx = filter(lambda (ctx, sh): not bool(sh.heap.dom()),
                              rctx)
        return classic_rctx

    def _satisfy(self, ctx, f):
        method_name = '_satisfy_' + type(f).__name__
        checker = getattr(self, method_name, self.generic_satisfy)
        return checker(ctx, f)

    def generic_satisfy(self, ctx, f):
        raise Exception('No model checker for ' +
                        str(f) + ':' + type(f).__name__)

    def _satisfy_FBase(self, ctx, f):
        nctx = ctx.mk_conj(f.pure)
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
            rid = f.root.id
            if rid in s:
                roots = [s.eval(f.root)]
            elif any(rid == v.id for v in ctx.exists_vars):
                roots = h.dom()
            else:
                debug('HData: Undeclared variable ' + rid)
                return []

            rctx_lst = []
            for root in roots:
                if root != Const.nil_addr:
                    if root not in h:
                        debug('HData: Cannot find the matched heap for ' + str(f))
                        return []
                    (typ, fields) = h.get(root)
                    if typ == f.name:
                        nh = h.clone()
                        ns = s.clone()
                        nh.remove(root)
                        if rid not in s:
                            ns.add(rid, Addr(root))

                        field_vals = map(lambda f: f.data.val, fields)
                        mconds = []
                        for (a, v) in zip(f.args, field_vals):
                            if isinstance(a, Null):
                                a = IConst(Const.nil_addr)
                            mconds.append(PBinRel(a, RelOp.EQ, IConst(v)))
                            if (isinstance(a, Var) and
                                isinstance(a.typ, TData) and
                                not ns.contains(a.id)):
                                ns.add(a.id, Addr(v)) # Instantiation
                        if mconds:
                            mcond = reduce(lambda m1, m2: m1.mk_conj(m2), mconds)
                            nctx = ctx.mk_conj(mcond)
                        else:
                            nctx = ctx
                        if not ns.is_unsat(nctx.state):
                            nsh = SHModel(ns, nh)
                            nsh.add_prog(self.prog)
                            rctx_lst.append((nctx, nsh))
            return rctx_lst

    def _satisfy_HPred(self, ctx, f):
        pred_defn = self.prog.lookup(f.name)
        sst = VarUtil.mk_subst(pred_defn.params, f.args)
        sst_pred_defn = pred_defn.subst(sst)
        # debug(sst_pred_defn)

        cases = sst_pred_defn.cases
        def wp(cases, Q):
            def process_cases(cases):
                nctx = []
                for case in cases:
                    pcond = case.get_pure()
                    pctx = ctx.mk_conj(pcond)
                    if not self.stack.is_unsat(pctx.state):
                        sh = self.clone()
                        rctx = sh._satisfy(pctx, case.get_heap())
                        nctx.extend(rctx)
                return nctx
            return Utils.wprocess(cases, process_cases, Q)

        rctx = Utils.runMP("satisfy_HPred",
                           cases, wp, chunksiz = 1,
                           doMP = settings.doMP and len(cases) >= 2)

        return rctx

    def _satisfy_HStar(self, ctx, f):
        hdata_lst, hpred_lst = f.heap_par()
        rctx = [(ctx, self)]
        for dp in (hdata_lst + hpred_lst):
            rcx = []
            for (cx, sh) in rctx:
                # debug(dp)
                r = sh._satisfy(cx, dp)
                # debug(r)
                rcx.extend(r)
            rctx = rcx
        return rctx

    def _satisfy_FExists(self, ctx, f):
        nctx = ctx.add_vars(f.vars)
        return self._satisfy(nctx, f.form)

    def group_by(self, func, ls):
        grouped = {}
        for elem in ls:
            key = func(elem)
            grouped.setdefault(key, []).append(elem)
        return grouped


