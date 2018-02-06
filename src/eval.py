from seplogic import *
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

class Eval(object):
    def eval(self, stk, e):
        method_name = 'eval_' + type(e).__name__
        evaluation = getattr(self, method_name, self.generic_eval)
        return evaluation(stk, e)

    def generic_eval(self, stk, e):
        raise Exception('No evaluation for ' + type(e).__name__)

class SHEval(Eval):
    def __init__(self):
        pass

    def eval_Var(self, stk, e):
        return stk[e.id].val

    def eval_IConst(self, stk, e):
        return e.val

    def eval_BinOp(self, stk, e):
        el = self.eval(stk, e.left)
        er = self.eval(stk, e.right)
        return ops[e.op](el, er)

    def eval_BConst(self, stk, e):
        return e.val

    def eval_PBinRel(self, stk, e):
        el = self.eval(stk, e.left)
        er = self.eval(stk, e.right)
        return ops[e.op](el, er)

    def eval_PNeg(self, stk, e):
        ev = self.eval(stk, e)
        return (not ev)

    def eval_PConj(self, stk, e):
        el = self.eval(stk, e.left)
        er = self.eval(stk, e.right)
        return (el and er)

    def eval_PDisj(self, stk, e):
        el = self.eval(stk, e.left)
        er = self.eval(stk, e.right)
        return (el or er)




