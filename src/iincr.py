from seplogic import *
from model import *
from trace import *
from utils import *
from debug import *
from printer import *
import itertools

class SingletonModel(object):
    def __init__(self, root, children_lst, sh, stk_addrs_dict):
        self.root = root
        self.children_lst = children_lst
        self.stk_addrs_dict = stk_addrs_dict
        self.sh = sh

    def __str__(self):
        return (self.root + ' -> ' + Printer.str_of_list(self.children_lst) + str(self.sh))

    def is_singleton_heap(self):
        return len(self.sh.heap.dom()) == 1

    def is_empty_heap(self):
        return len(self.sh.heap.dom()) == 0

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
        singleton_model = SingletonModel(root, children_lst, ssh, stk_addrs_dict)
        return (singleton_model, h2)

    @classmethod
    def _split_heap(self, h, start_addr, stk_addrs):
        working_set = [start_addr]
        marked_addrs = []
        stk_children = [start_addr]
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
    def __init__(self, id, loc, local_vars, stk_addrs_dict, ctx, sh, ret):
        self.id = id
        self.loc = loc
        self.local_vars = local_vars
        self.stk_addrs_dict = stk_addrs_dict
        self.ctx = ctx
        self.sh = sh
        self.ret = ret

    def __str__(self):
        return ('\n' + str(self.loc) + ' - ' + str(self.id) + ':\n' +
                Printer.str_of_list(self.local_vars) + ':\n' +
                str(self.ctx) + '\n' + str(self.sh) + '\n' +
                ('return: ' + str(self.ret) if self.ret else ''))

    def clone(self):
        return copy.deepcopy(self)

    def is_same_heap_dom(self, other):
        return set(self.sh.heap.dom()) == set(other.sh.heap.dom())

    @classmethod
    def collect_addrs_from_stk(self, s):
        stk_addrs_dict = {}
        for v in s:
            vl = s.get(v)
            if isinstance(vl, Addr):
                addr = vl.val
                List.add_lst_dict(stk_addrs_dict, addr, v)
        return stk_addrs_dict

    @classmethod
    def make(self, local_vars, model):
        nsh = model.sh.clone()
        stk_addrs_dict = self.collect_addrs_from_stk(nsh.stack)
        init_ctx = Context.mk_init_context()
        return MetaModel(model.id, model.loc, local_vars,
                         stk_addrs_dict, init_ctx, nsh, model.ret)

class IIncr(object):
    @classmethod
    def infer(self, prog, models):
        # debug(models)
        if not models:
            return []

        local_ptr_vars_lst = map(lambda model:
                                 filter(lambda v:
                                        isinstance(model.sh.stack.get(v), Addr),
                                        model.sh.stack.dom()),
                                 models)
        local_ptr_vars = list(set.intersection(*(map(lambda vs:
                                                     set(vs),
                                                     local_ptr_vars_lst))))
        # debug(local_ptr_vars)
        meta_models = map(lambda model: MetaModel.make(local_ptr_vars, model), models)
        f_residue_lst = self._infer_root_lst(prog, local_ptr_vars, meta_models)
        if not f_residue_lst:
            f_residue_lst = [(HEmp(), meta_models)]
        res_lst =[]
        for (f, residue_models) in f_residue_lst:
            # debug(f)
            # debug(residue_models)
            # vars = map(lambda v: Var(v), local_ptr_vars)
            vs = (set(local_ptr_vars) | f.fv() |
                  (set(map(lambda v: v.id, f.vars)) if isinstance(f, FExists) else set()))
            vars = map(lambda v: Var(v), list(vs))
            pf = self._infer_pure_ptr(vars, residue_models)
            f = f.mk_conj(pf) if pf is not None else f
            res_lst.append((f, residue_models))

            # for (model, residue_model) in zip(models, residue_models):
            #     debug(model)
            #     debug(residue_model)
        # debug(res_lst)
        return res_lst

    @classmethod
    def _infer_pure_ptr(self, vars, meta_models):
        vars_with_nil = vars + [Null()]
        if all(model.ret is not None for model in meta_models):
            res = Var(Const.res)
            vars_with_nil.append(res)
            for model in meta_models:
                model.sh.stack.add(Const.res, model.ret)
        pairs = list(itertools.combinations(vars_with_nil, 2))
        eq_constrs = map(lambda (v1, v2): PBinRel(v1, RelOp.EQ, v2), pairs)
        valid_eq_constrs = filter(lambda c:
            all(mm.sh.stack.is_unsat(mm.ctx.state.mk_conj(PNeg(c)))
                for mm in meta_models),
            eq_constrs)
        if valid_eq_constrs:
            pf = reduce(lambda c1, c2: c1.mk_conj(c2), valid_eq_constrs)
            return pf

    @classmethod
    def _infer_root_lst(self, prog, roots, meta_models):
        if not roots:
            return []
        else:
            f_residue_lst = []
            root = roots[0]
            f_unconsumed_models_lst = self._infer_root(prog, root, meta_models)
            if not f_unconsumed_models_lst:
                # debug('Cannot derive formulas for the root pointer ' + root)
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

        root_aliases = set.intersection(*(map(lambda model:
                                              set(model.stk_addrs_dict[model.sh.stack.get(
                                                  root).val]),
                                              meta_models)))
        root_aliases = set(map(lambda v: Var(v), root_aliases))
        # debug(root_aliases)

        residue_models_lst = []

        # # Heuristic 1
        # for children in root_children_lst:
        #     residue_models_lst.extend(self._infer_pred_lst(prog, root,
        #                                                    children,
        #                                                    singleton_models))

        # # Heuristic 2
        # for children in root_children_lst:
        #     residue_models = self._infer_pred_lst(prog, root, children, singleton_models)
        #     if residue_models:
        #         residue_models_lst.extend(residue_models)
        #         break

        # Heuristic 3
        # debug(root_children_lst)
        root_children_grp = List.group_by(lambda children:
                                          len(set(children) - root_aliases),
                                          root_children_lst)
        # debug(root_children_grp)
        for l in sorted(root_children_grp.keys(), reverse=True):
            for children in root_children_grp[l]:
                residue_models = self._infer_pred_lst(prog, root, children, singleton_models)
                residue_models_lst.extend(residue_models)
            if residue_models_lst:
                break

        def mk_unconsumed_models(f, residue_models):
            unconsumed_rheaps = map(lambda (rh, (ctx, rsh)): (ctx, rh.union(rsh.heap)),
                                    zip(rem_heaps, residue_models))
            unconsumed_models = []
            for (meta_model, (ctx, unconsumed_heap)) in zip(meta_models, unconsumed_rheaps):
                unconsumed_model = meta_model.clone()
                unconsumed_model.sh.heap = unconsumed_heap
                unconsumed_model.ctx = unconsumed_model.ctx.combine(ctx)
                unconsumed_models.append(unconsumed_model)
            return (f, unconsumed_models)

        return map(lambda (f, residue_models):
                   mk_unconsumed_models(f, residue_models), residue_models_lst)

    @classmethod
    def _infer_pred_lst(self, prog, root, children, singleton_models):
        if all(model.is_empty_heap() for model in singleton_models):
            return []
        else:
            pred_lst = []
            for pred_defn in prog.pred_defn_lst:
                preds = self._infer_pred(prog, pred_defn, root,
                                         children, singleton_models)
                pred_lst.extend(preds)

            if all(model.is_singleton_heap() for model in singleton_models):
                data_lst = self._infer_data(prog, root, children, singleton_models)
                pred_lst.extend(data_lst)

            return pred_lst

    @classmethod
    def _infer_validate(self, f, singleton_models):
        # debug(f)
        # debug(singleton_models)
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
                (ctx, rsh) = rctx
                residue_models.append(rctx)
                any_decr_models = (any_decr_models or
                                   (len(rsh.heap.dom()) == 0) or
                                    len(rsh.heap.dom()) < len(sh.heap.dom()))
            # debug(any_decr_models)
        if all_is_valid and any_decr_models:
            # # For getting all residue contexts
            # residue_tuple_lst = list(itertools.product(*residue_models_lst))
            # debug(len(residue_tuple_lst))
            # fs.extend(map(lambda residue_models: (f, residue_models),
            #               residue_tuple_lst))

            # debug(f)
            # debug(residue_models)
            return (f, residue_models)

    @classmethod
    def _infer_pred(self, prog, pred_defn, root, children, singleton_models):
        # debug(root)
        # debug(singleton_models)
        pred_template = HPred(pred_defn.name, pred_defn.params)

        prim_params = []
        ptr_params = []
        for param in pred_defn.params:
            if isinstance(param.typ, TData):
                ptr_params.append(param)
            else:
                prim_params.append(param)

        prim_sst = map(lambda param: (param, VarUtil.mk_fresh(param)), prim_params)

        def get_type(var):
            try:
                var_typ_lst = []
                for model in singleton_models:
                    s = model.sh.stack
                    h = model.sh.heap
                    var_addr = s.get(var)
                    if var_addr.val == Const.nil_addr:
                        var_typ = TNull()
                        var_typ_lst.append(var_typ)
                    elif len(h.dom()) != 0:
                        typ, _ = h.get(var_addr.val)
                        var_typ = TData(typ)
                        var_typ_lst.append(var_typ)

                if var_typ_lst:
                    nil_typ_lst, data_typ_lst = List.partition(lambda t: 
                                                               isinstance(t, TNull),
                                                               var_typ_lst)
                    if not data_typ_lst:
                        return TNull()
                    else:
                        if List.all_is_identical(data_typ_lst):
                            return data_typ_lst[0]
            except:
                pass
            
        assert len(ptr_params) > 0
        root_param = ptr_params[0]

        root_typ = get_type(root)
        if (not root_typ) or (not root_typ.is_sub_type(root_param.typ)):
            return []
        
        root_arg = Var(root)
        root_sst = (root_param, root_arg)

        # debug(root)
        # debug(children)

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

            validate_res = self._infer_validate(f, singleton_models)
            if validate_res:
                fs.append(validate_res)
        # debug(root)
        # debug(fs)
        return fs

    @classmethod
    def _infer_data(self, prog, root, children, singleton_models):
        data_node_lst = []
        for model in singleton_models:
            s = model.sh.stack
            h = model.sh.heap
            root_addr = s.get(root)
            data_typ, data_fields = h.get(root_addr.val)
            args_lst = []
            for field in data_fields:
                if isinstance(field, PtrField):
                    addr = field.data.val
                    if addr in model.stk_addrs_dict:
                        arg_vars = model.stk_addrs_dict[field.data.val]
                        args = map(lambda v: Var(v), arg_vars)
                    elif addr == Const.nil_addr:
                        args = [Null()]
                    else:
                        args = []
                else:
                    args = []
                args_lst.append(set(args))
            data_node_lst.append((data_typ, args_lst))

        if (bool(data_node_lst) and 
            List.all_is_identical(map(lambda (typ, _): typ, data_node_lst))):
            data_typ, _ = data_node_lst[0]
            arg_grp_tuples = zip(*(map(lambda (_, args): args, data_node_lst)))
            args_tuples = map(lambda arg_grp:
                              list(set.intersection(*arg_grp)),
                              arg_grp_tuples)
            args_tuples = map(lambda args: args if bool(args) else [VarUtil.mk_fresh()],
                              args_tuples)
            args_lst = list((itertools.product(*args_tuples)))
            data_lst = map(lambda args: HData(Var(root, typ = TData(data_typ)),
                                              data_typ, args),
                           args_lst)
            ds = []
            for data in data_lst:
                validate_res = self._infer_validate(data, singleton_models)
                if validate_res:
                    ds.append(validate_res)
                return ds
        else:
            return []

    @classmethod
    def _get_common_children(self, root, singleton_models):
        lst_of_model_children = map(lambda model: model.children_lst, singleton_models)

        # for model in singleton_models:
        #     debug(model)

        lst_of_children = list(itertools.product(*lst_of_model_children))
        # debug(lst_of_children)
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






