from seplogic import *
from model import *
from trace import *
from utils import *
from debug import *
from printer import *
import itertools

class SingletonModel(object):
    def __init__(self, root, children_lst, sh):
        self.root = root
        self.children_lst = children_lst
        self.sh = sh

    def __str__(self):
        return (self.root + ' -> ' + Printer.str_of_list(self.children_lst) + str(self.sh))

    @classmethod
    def make(self, sh, root, stk_addrs_dict):
        ssh = sh.clone()
        s = ssh.stack
        h = ssh.heap
        root_addr = s.get(root).val
        stk_addrs = stk_addrs_dict.keys()
        # Collect reachable heap addresses from root_addr and its boundary
        singleton_heap_dom, children_addrs, dangling_addrs = self._split_heap(h,
                                                                              root_addr,
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
        singleton_model = SingletonModel(root, children_lst, ssh)
        return (singleton_model, h2)

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
            elif parent == Const.nil_addr:
                stk_children.append(parent)
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
        return (Printer.str_of_list(self.local_vars) + ': ' + str(self.sh))

    def clone(self):
        return copy.deepcopy(self)

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
        f_residue_lst = self._infer_root_lst(prog, local_ptr_vars, meta_models)
        for (f, residue_model) in f_residue_lst:
            debug(f)
        return f_residue_lst

    @classmethod
    def _infer_root_lst(self, prog, roots, meta_models):
        if not roots:
            return []
        else:
            f_residue_lst = []
            root = roots[0]
            f_unconsumed_models_lst = self._infer_root(prog, root, meta_models)
            if not f_unconsumed_models_lst:
                debug('Cannot derive formulas for the root pointer ' + root)
                return self._infer_root_lst(prog, roots[1:], meta_models)
            else:
                for (f, unconsumed_models) in f_unconsumed_models_lst:
                    fs_unconsumed_models_lst = self._infer_root_lst(prog, roots[1:],
                                                                    unconsumed_models)
                    if not fs_unconsumed_models_lst:
                        f_residue_lst.append((f, unconsumed_models))
                    else:
                        f_residue_lst.extend(
                            map(lambda (fs, unconsumed_models): (f.mk_conj(fs),
                                                                 unconsumed_models),
                                fs_unconsumed_models_lst))
            return f_residue_lst

    @classmethod
    def _infer_root(self, prog, root, meta_models):
        unconsumed_models_lst = []
        f_unconsumed_models_lst = self._infer_singleton_models(prog, root, meta_models)
        unconsumed_models_lst.extend(f_unconsumed_models_lst)
        return unconsumed_models_lst

    @classmethod
    def _infer_singleton_models(self, prog, root, meta_models):
        singleton_models, rem_heaps = zip(*(map(lambda model:
                                                SingletonModel.make(model.sh, root,
                                                                    model.stk_addrs_dict),
                                                meta_models)))
        root_children_lst = self._get_common_children(root, singleton_models)
        # debug(root)
        # debug(root_children_lst)

        residue_models_lst = []

        # for children in root_children_lst:
        #     residue_models_lst.extend(self._infer_pred_lst(prog, root,
        #                                                    children,
        #                                                    singleton_models))

        for children in root_children_lst:
            residue_models = self._infer_pred_lst(prog, root, children, singleton_models)
            if residue_models:
                residue_models_lst.extend(residue_models)
                break

        # root_children_grp = List.group_by(len, root_children_lst)
        # for l in sorted(root_children_grp.keys(), reverse=True):
        #     for children in root_children_grp[l]:
        #         residue_models = self._infer_pred_lst(prog, root, children, singleton_models)
        #         residue_models_lst.extend(residue_models)
        #     if residue_models_lst:
        #         break

        def mk_unconsumed_models(f, residue_models):
            unconsumed_heaps = map(lambda (rh, rsh): rh.union(rsh.heap),
                                   zip(rem_heaps, residue_models))
            unconsumed_models = []
            for (meta_model, unconsumed_heap) in zip(meta_models, unconsumed_heaps):
                unconsumed_model = meta_model.clone()
                unconsumed_model.sh.heap = unconsumed_heap
                unconsumed_models.append(unconsumed_model)
            return (f, unconsumed_models)

        return map(lambda (f, residue_models):
                   mk_unconsumed_models(f, residue_models), residue_models_lst)

    @classmethod
    def _infer_pred_lst(self, prog, root, children, singleton_models):
        pred_lst = []
        for pred_defn in prog.pred_defn_lst:
            preds = self._infer_pred(prog, pred_defn, root,
                                     children, singleton_models)
            pred_lst.extend(preds)
        return pred_lst

    @classmethod
    def _infer_pred(self, prog, pred_defn, root, children, singleton_models):
        pred_template = HPred(pred_defn.name, pred_defn.params)

        prim_params = []
        ptr_params = []
        for param in pred_defn.params:
            if isinstance(param.typ, TData):
                ptr_params.append(param)
            else:
                prim_params.append(param)

        prim_sst = map(lambda param: (param, VarUtil.mk_fresh(param)), prim_params)

        assert len(ptr_params) > 0
        root_param = ptr_params[0]
        root_arg = Var(root)
        root_sst = (root_param, root_arg)

        if len(children) < len(ptr_params) - 1:
            num_fresh_vars = len(ptr_params) - 1 - len(children)
            children.extend([Const.fresh_vars_dummy_addr] * num_fresh_vars)
        ptr_args_lst = []
        children_permutations = set(
            itertools.permutations(children, len(ptr_params) - 1))
        for perm in list(children_permutations):
            perm = map(lambda arg: VarUtil.mk_fresh()
                       if arg == Const.fresh_vars_dummy_addr else arg, perm)
            ptr_args_lst.append(perm)

        ptr_sst_lst = map(lambda ptr_args: zip(ptr_params[1:], ptr_args),
                          ptr_args_lst)
        sst_lst = map(lambda ptr_sst: [root_sst] + ptr_sst + prim_sst,
                      ptr_sst_lst)
        sst_lst = map(lambda sst: VarUtil.mk_subst(*(zip(*sst))), sst_lst)
        stk_ids = [root] + map(lambda v: v.id, filter(lambda v: isinstance(v, Var),
                                                      children))
        fs = []
        for sst in sst_lst:
            pred = pred_template.subst(sst)
            fbase = FBase(pred, BConst(True))
            exists_vars = map(lambda vid: Var(vid),
                              filter(lambda vid: vid not in stk_ids,
                                     fbase.fv()))
            if exists_vars:
                f = FExists(exists_vars, fbase)
            else:
                f = fbase

            all_is_valid = True
            any_decr_models = False
            residue_models = []
            for model in singleton_models:
                sh = model.sh
                rctx = sh.get_smallest_residue_ctx(f)
                all_is_valid = rctx is not None
                if not all_is_valid:
                    break
                else:
                    (_, rsh) = rctx
                    residue_models.append(rsh)
                    any_decr_models = (any_decr_models or
                                       (len(rsh.heap.dom()) == 0) or
                                        len(rsh.heap.dom()) < len(sh.heap.dom()))
                # debug(any_decr_models)
            if all_is_valid and any_decr_models:
                # residue_tuple_lst = list(itertools.product(*residue_models_lst))
                # debug(len(residue_tuple_lst))
                # fs.extend(map(lambda residue_models: (f, residue_models),
                #               residue_tuple_lst))
                fs.append((f, residue_models))
        return fs

    @classmethod
    def _get_common_children(self, root, singleton_models):
        lst_of_model_children = map(lambda model: model.children_lst, singleton_models)
        lst_of_children = list(itertools.product(*lst_of_model_children))
        no_dups_children = map(lambda children_lst:
                               list(set.intersection(*(map(lambda vs: set(vs), children_lst)))
                                    - set([Var(root)])),
                               lst_of_children)

        no_dups_ss_children = []
        for children in no_dups_children:
            no_dups_ss_children.extend(List.all_subsets(children))

        no_dups_ss_children.sort(key=lambda c: (len(c), Null() not in c), reverse=True)
        # no_dups_ss_children.sort(key=len, reverse=True)
        subset_children = []
        for children in no_dups_ss_children:
            if not(any(set(children) == set(s) for s in subset_children)):
                subset_children.append(children)
        return subset_children






