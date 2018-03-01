from seplogic import *
from trace import *
from model import *
from debug import *
from typ import *
from utils import *
import networkx as nx

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
        self.mk_spatial_atom(stk_addrs_dict, submodel)

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
        if len(dom_h) == 0:
            self.mk_emp()
        else:
            if len(dom_h) == 1:
                self.mk_singleton(stk_addrs_dict, sh)
            self.mk_pred()

    def mk_emp(self):
        return HEmp()

    def mk_singleton(self, stk_addrs_dict, sh):
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
            else:
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

        assert sh.classic_satisfy(f)
        debug(f)
        return f

    def mk_pred(self):
        pass

class SLInfer(object):
    @classmethod
    def infer(self, sh):
        stk_addrs_dict = self.collect_addrs_from_stk(sh.stack)
        stk_addrs = stk_addrs_dict.keys()
        debug(stk_addrs)
        debug(sh.heap)
        heap_partitions = self.partition_heap(sh.heap, stk_addrs)
        debug(heap_partitions)
        for hp in heap_partitions:
            hp.slinfer(stk_addrs_dict, sh)

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
            debug(sorted_scc_lst)
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
                            child != 0):
                            working_set.append(child)
                        if (child in stk_addrs):
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


