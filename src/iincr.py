from seplogic import *
from trace import *
from utils import *
from debug import *
from printer import *
import itertools

class SingletonModel(object):
    def __init__(self, root_id, childen_lst, sh):
        self.root_id = root_id
        self.children_lst = children_lst
        self.sh = sh

    def __str__(self):
        return (root_id + ' -> ' + Printer.str_of_list(self.children_lst) + str(self.sh))

    @classmethod
    def make(self, sh, var, stk_addrs_dict):
        ssh = sh.clone()
        s = ssh.stack
        h = ssh.heap
        var_addr = s.get(var).val
        stk_addrs = stk_addrs_dict.keys()
        # Collect reachable heap addresses from var_addr and its boundary
        singleton_heap_dom, children_addrs, dangling_addrs = self._split_heap(h,
                                                                              var_addr,
                                                                              stk_addrs)
        children_vars = map(lambda child_addr:
                            self._get_addr_vars(stk_addrs_dict, None,
                                                child_addr, get_nil = True),
                             set(children_addrs))
        children_vars = filter(lambda children: bool(children), children_vars)
        children_lst = map(lambda vs: List.remove_dups(vs),
                           list(itertools.product(*children_vars)))
        h1 = Heap()
        h2 = Heap()
        for addr in h:
            if addr in singleton_heap_dom:
                h1.add(addr, h[addr])
            else:
                h2.add(addr, h[addr])
        ssh.heap = h1
        return SingletonModel(var, children_lst, ssh)

    @classmethod
    def _split_heap(self, h, start_addr, stk_addrs):
        working_set = [start_addr]
        marked_addrs = []
        stk_children = []
        dangling_children = []
        while working_set:
            parent = working_set[0]
            working_set = working_set[1:]
            if parent in h:
                _, fis = h[parent]
                marked_addrs.append(parent)
                for fi in fis:
                    if isinstance(fi.data, Addr):
                        child = fi.data.val
                        if (child not in stk_addrs and
                            child not in marked_addrs and
                            child != Const.nil_addr):
                            working_set.append(child)
                        if (child in stk_addrs or
                            child == Const.nil_addr):
                            stk_children.append(child)
            else:
                dangling_children.append(parent)
        return (marked_addrs, stk_children, dangling_children)

    @classmethod
    def _get_addr_vars(self, stk_addrs_dict, ty, addr, get_nil = False):
        try:
            vs = map(lambda v: Var(v), stk_addrs_dict[addr])
        except:
            vs = []
        finally:
            if get_nil and addr == Const.nil_addr:
                vs.append(Null())
        for v in vs:
            v.typ = ty
        return vs

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
            vl = s[v]
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
    def _infer_var(self, prog, var, meta_models_lst):
        for meta_models in meta_models_lst:
            preds = self._infer_models(prog, var, meta_models)
        return [], []

    @classmethod
    def _infer_models(self, prog, var, meta_models):
        for model in meta_models:
            singleton_model = SingletonModel.make(model.sh, var, model.stk_addrs_dict)
            debug(singleton_model)
            






