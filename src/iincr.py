from seplogic import *
from utils import *
from debug import *
from printer import *

class SingletonHeap(object):
    def __init__(self, root_id, childen_ids, sh):
        self.root_id = root_id
        self.children_ids = children_ids
        self.sh = sh

    def __str__(self):
        return (root_id + ' -> ' + Printer.str_of_list(self.children_ids)
                + str(self.sh))

class MetaModel(object):
    def __init__(self, local_vars, stk_addrs_dict, sh):
        self.local_vars = local_vars
        self.stk_addrs_dict = stk_addrs_dict
        self.sh = sh

    def __str__(self):
        return (Printer.str_of_list(self.local_vars) + ': ' +
                str(self.subheap))

    @classmethod
    def collect_addrs_from_stk(self, s):
        stk_addrs_dict = {}
        for v in s:
            vl = stk[v]
            if isinstance(vl, Addr):
                addr = vl.val
                List.add_lst_dict(stk_addrs_dict, addr, v)
        return stk_addrs_dict

    @classmethod
    def make(self, local_vars, sh):
        nsh = sh.clone()
        stk_addrs_dict = self.collect_addrs_from_stk(nsh.stack)
        return MetaModel(local_vars, stk_addrs_dict, nsh)

class IIncr(object):
    @classmethod
    def infer(self, prog, models):
        local_ptr_vars_lst = map(lambda sh:
                                 filter(lambda v:
                                        isinstance(sh.stack.get(v), Addr),
                                        sh.stack.dom()),
                                 models)
        local_ptr_vars = list(set.intersection(
            *(map(lambda vs: set(vs), local_ptr_vars_lst))))
        meta_models = map(lambda sh: MetaModel.make(local_ptr_vars, sh), models)
        fs = self._infer_var_lst(prog, local_ptr_vars, [meta_models])
        return []

    @classmethod
    def _infer_var_lst(self, prog, vars, meta_models_lst):
        for var in vars:
            preds, meta_models_lst = self._infer_var(prog, var,
                                                           meta_models_lst)

    @classmethod
    def _infer_incr_var(self, prog, var, meta_models_lst):
        for meta_models in meta_models_lst:
            preds = self._infer_models(prog, var, meta_models)
        return [], []

    @classmethod
    def _infer_models(self, prog, var, meta_models):
        for model in meta_models:
            s = model.sh.stack
            h = model.sh.heap
            var_addr = s.get(var).val
            stk_addrs = model.stk_addrs_dict.keys()
            self.partition_heap_singleton(h, var_addr, stk_addrs)






