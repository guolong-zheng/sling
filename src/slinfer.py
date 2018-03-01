from seplogic import *
from trace import *
from model import *
from debug import *
from typ import *
from utils import *
import networkx as nx

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
            self.slinfer_heap_partition(stk_addrs_dict, sh, hp)

    @classmethod
    def slinfer_heap_partition(self, stk_addrs_dict, sh, hp):
        s = sh.stack
        h = sh.heap
        prog = sh.prog
        stk_addrs, heap_addrs = hp
        stk_vars = map(lambda sa: stk_addrs_dict[sa], stk_addrs)
        params = map(lambda vs: vs[0], stk_vars)
        debug(params)
        sub_heap = Heap()
        for ha in heap_addrs:
            sub_heap.add(ha, h[ha])
        debug(sub_heap)


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
                    marked_addrs.extend(group)
            return(groups)

    @classmethod
    def _split_heap(self, h, start, stk_addrs, marked_addrs):
        working_set = [start]
        group = []
        stk_addrs_params = []
        if start in stk_addrs:
            stk_addrs_params.append(start)
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
                            stk_addrs_params.append(child)
        return (stk_addrs_params, group)

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


