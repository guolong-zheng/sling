from seplogic import *

class ModelChecker(object):
    def check(self, model, f):
        method_name = 'check_' + type(f).__name__
        checker = getattr(self, method_name, self.generic_check)
        return checker(model, f)

    def generic_check(self, model, f):
        raise Exception('No model checker for ' + type(f).__name__)

class SHModelChecker(ModelChecker):
    def __init__(self):
        pass

    def check_FBase(self, model, f):
        if f.is_emp():
            self.check(model, f.pure)

    def check_PBinRel(self, model, f):



