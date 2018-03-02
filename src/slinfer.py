from seplogic import *
from trace import *
from model import *
from debug import *
from typ import *
from utils import *
import networkx as nx
import itertools

class SubHeap(object):
    def __init__(self, root, children, dangling_children, dom):
        self.root = root
        self.children = children
        self.dangling_children = dangling_children
        self.dom = dom

    def __str__(self):
        return (str(self.root) + '->' + str(self.children)
                + ': ' + str(self.dom))

    def mk_submodel(self, sh):
        h = sh.heap
        sub_heap = Heap()
        for addr in self.dom:
            sub_heap.add(addr, h[addr])
        return SHModel(sh.stack, sub_heap, sh.prog)

    def slinfer(self, stk_addrs_dict, sh):
        submodel = self.mk_submodel(sh)
        return self.mk_spatial_atom(stk_addrs_dict, submodel)

    def mk_alias(self, stk_addrs_dict, ty, addr):
        try:
            vs = map(lambda v: Var(v), stk_addrs_dict[addr])
        except:
            vs = [VarUtil.mk_fresh()]
        assert vs
        for v in vs:
            v.typ = ty
        x = vs[0]
        eqs = []
        if addr == Const.nil_addr:
            eqs.append(PBinRel(x, '=', Null()))
        else:
            for y in vs[1:]:
                eqs.append(PBinRel(x, '=', y))
        if not eqs:
            aliasing_cond = BConst(True)
        else:
            aliasing_cond = reduce(lambda c1, c2: PConj(c1, c2), eqs)
        return x, aliasing_cond

    def mk_spatial_atom(self, stk_addrs_dict, sh):
        h = sh.heap
        dom_h = h.dom()
        atoms = []
        if len(dom_h) == 0:
            atoms.append(self.mk_emp())
        else:
            if len(dom_h) == 1:
                atoms.append(self.mk_singleton(stk_addrs_dict, sh))
            atoms.extend(self.mk_pred_lst(stk_addrs_dict, sh))
        return atoms

    def mk_emp(self):
        return HEmp()

    def mk_singleton(self, stk_addrs_dict, sh):
        # debug(sh)
        rty, fis = sh.heap[self.root]
        root_var, aliasing_root = self.mk_alias(stk_addrs_dict, rty, self.root)
        root_var.typ = Type.typ(rty)
        data_defn = sh.prog.lookup(rty)
        atys = map(lambda fi: Type.typ(fi.typ), data_defn.fields)
        args = []
        pf = BConst(True)
        for aty, fi in zip(atys, fis):
            if isinstance(fi, DataField):
                arg_var = VarUtil.mk_fresh()
                arg_var.typ = aty
            else: # isinstance(fi, PtrField)
                arg_var, aliasing_arg = self.mk_alias(stk_addrs_dict, aty, fi.data.val)
                pf = pf.mk_conj(aliasing_arg)
            args.append(arg_var)
        pdata = HData(root_var, rty, args)
        fbase = pdata.mk_conj(pf)
        stk_vars = List.flatten(stk_addrs_dict.values())
        exists_vars = filter(lambda v: v.id not in stk_vars, args)
        if exists_vars:
            f = FExists(exists_vars, fbase)
        else:
            f = fbase
        # debug(f)
        assert sh.classic_satisfy(f)
        return f

    def mk_pred_lst(self, stk_addrs_dict, sh):
        pred_lst = []
        for pred_defn in sh.prog.pred_defn_lst:
            preds = self.mk_pred(pred_defn, stk_addrs_dict, sh)
            pred_lst.extend(preds)
        # debug(pred_lst)
        return pred_lst

    def mk_pred(self, pred_defn, stk_addrs_dict, sh):
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
        root_arg, _ = self.mk_alias(stk_addrs_dict, root_param.typ, self.root)
        root_sst = (root_param, root_arg)

        ptr_args = []
        pf = BConst(True)
        for child in self.children:
            # debug(child)
            ptr_arg, aliasing_arg = self.mk_alias(stk_addrs_dict, None, child)
            ptr_args.append(ptr_arg)
            pf = pf.mk_conj(aliasing_arg)
        ptr_args_mutation = list(itertools.product(ptr_args,
                                                   repeat=len(ptr_params)-1))
        ptr_ssts = []
        for mut in ptr_args_mutation:
            ptr_sst = zip(ptr_params[1:], list(mut))
            ptr_ssts.append(ptr_sst)

        if ptr_ssts:
            ssts = map(lambda ptr_sst: [root_sst] + ptr_sst + prim_sst, ptr_ssts)
        else:
            ssts = [[root_sst] + prim_sst]

        fs = []
        pred_template = HPred(pred_defn.name, pred_defn.params)
        stk_vars = List.flatten(stk_addrs_dict.values())
        exists_prim_args = map(lambda (_, pa): pa, prim_sst)
        exists_ptr_args = filter(lambda v: v.id not in stk_vars, ptr_args)
        exists_args = exists_prim_args + exists_ptr_args
        ssts = map(lambda sst: VarUtil.mk_subst(*(zip(*sst))), ssts)
        for sst in ssts:
            pred = pred_template.subst(sst)
            fbase = FBase(pred, BConst(True))
            if exists_args:
                f = FExists(exists_args, fbase)
            else:
                f = fbase
            fs.append(f)
        # debug(fs)
        fs = filter(lambda f: sh.classic_satisfy(f), fs)
        return fs

class SLInfer(object):
    @classmethod
    def infer(self, sh):
        stk_addrs_dict = self.collect_addrs_from_stk(sh.stack)
        stk_addrs = stk_addrs_dict.keys()
        heap_partitions = self.partition_heap(sh.heap, stk_addrs)
        conj_preds_lst = []
        for hp in heap_partitions:
            pred_lst = hp.slinfer(stk_addrs_dict, sh)
            conj_preds_lst.append(pred_lst)
        fs = []
        for conj_preds in itertools.product(*conj_preds_lst):
            f = reduce(lambda f1, f2: f1.mk_conj(f2), conj_preds)
            # debug(f)
            fs.append(f)
        return fs

    @classmethod
    def collect_addrs_from_stk(self, stk):
        stk_addrs_dict = {}
        for v in stk:
            a = stk[v]
            if isinstance(a, Addr):
                val = a.val
                if val not in stk_addrs_dict:
                    stk_addrs_dict[val] = [v]
                else:
                    stk_addrs_dict[val].append(v)
        return stk_addrs_dict

    @classmethod
    def partition_heap(self, h, stk_addrs):
        if not h:
            return []
        else:
            dg = self._build_dependency_graph(h)
            sccs = nx.strongly_connected_component_subgraphs(dg)
            sg = self._build_scc_graph(dg, sccs)
            sorted_sccs = nx.topological_sort(sg)
            sorted_scc_lst = [list(scc.nodes) for scc in sorted_sccs]
            # debug(sorted_scc_lst)
            marked_addrs = []
            groups = []
            for scc in sorted_scc_lst:
                start_addrs = filter(lambda a: (a in stk_addrs and
                                                a not in marked_addrs), scc)
                for start in start_addrs:
                    group = self._split_heap(h, start, stk_addrs, marked_addrs)
                    groups.append(group)
                    marked_addrs.extend(group.dom)
            return(groups)

    @classmethod
    def _split_heap(self, h, start, stk_addrs, marked_addrs):
        working_set = [start]
        group = []
        stk_children = []
        dangling_children = []
        # if start in stk_addrs:
        #     stk_addrs_params.append(start)
        while working_set:
            parent = working_set[0]
            working_set = working_set[1:]
            if parent in h:
                _, fis = h[parent]
                marked_addrs.append(parent)
                group.append(parent)
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
        return SubHeap(start, stk_children, dangling_children, group)

    @classmethod
    def _build_dependency_graph(self, h):
        dg = nx.DiGraph()
        for addr in h:
            dg.add_node(addr)
            _, fis = h[addr]
            for fi in fis:
                if isinstance(fi.data, Addr):
                    dg.add_edge(addr, fi.data.val)
        return dg

    @classmethod
    def _build_scc_graph(self, dg, sccs):
        scc_dict = {}
        for scc in sccs:
            for node in scc.nodes:
                scc_dict[node] = scc

        sg = nx.DiGraph()
        for edge in dg.edges:
            n1, n2 = edge
            scc1 = scc_dict[n1]
            scc2 = scc_dict[n2]
            sg.add_nodes_from([scc1, scc2])
            if scc1 != scc2:
                sg.add_edge(scc1, scc2)
        return sg


