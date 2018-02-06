from seplogic import *

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
        return stk[e.id]




