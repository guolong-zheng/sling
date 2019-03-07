from seplogic import Ternary
from debug import *
from itertools import *
import z3

class MP(object):
    @classmethod
    def getWorkloads(cls, tasks, maxProcessces, chunksiz):
        """
        >>> wls = Miscs.getWorkloads(range(12),7,1); wls
        [[0, 1], [2, 3], [4, 5], [6, 7], [8, 9], [10, 11]]

        >>> wls = Miscs.getWorkloads(range(12),5,2); wls
        [[0, 1], [2, 3], [4, 5], [6, 7], [8, 9, 10, 11]]

        >>> wls = Miscs.getWorkloads(range(20),7,2); wls
        [[0, 1, 2], [3, 4, 5], [6, 7, 8], [9, 10, 11], [12, 13, 14], [15, 16, 17], [18, 19]]

        >>> wls = Miscs.getWorkloads(range(20),20,2); wls
        [[0, 1], [2, 3], [4, 5], [6, 7], [8, 9], [10, 11], [12, 13], [14, 15], [16, 17], [18, 19]]
        """
        assert len(tasks) >= 1, tasks
        assert maxProcessces >= 1, maxProcessces
        assert chunksiz >= 1, chunksiz

        # Determine # of processes
        ntasks = len(tasks)
        nprocesses = int(round(ntasks/float(chunksiz)))
        if nprocesses > maxProcessces:
            nprocesses = maxProcessces

        # Determine workloads 
        cs = int(round(ntasks/float(nprocesses)))
        wloads = []
        for i in range(nprocesses):
            s = i*cs
            e = s+cs if i < nprocesses-1 else ntasks
            wl = tasks[s:e]
            if wl:  # Could be 0, e.g., getWorkloads(range(12),7,1)
                wloads.append(wl)

        return wloads

    @classmethod
    def runMP(cls, taskname, tasks, wprocess, chunksiz, doMP):
        """
        Run wprocess on tasks in parallel
        """
        if doMP:
            from multiprocessing import (Process, Queue, cpu_count)
            Q = Queue()
            wloads = cls.getWorkloads(tasks,
                                      maxProcessces = cpu_count(),
                                      chunksiz = chunksiz)

            # debug("workloads '{}' {}: {}"
            #       .format(taskname, len(wloads), map(len,wloads)))

            workers = [Process(target = wprocess,
                               args = (wl, Q)) for wl in wloads]
            for w in workers: w.start()
            wrs = []
            for _ in workers: wrs.extend(Q.get())
        else:
            wrs = wprocess(tasks, Q = None)

        return wrs

    @classmethod
    def wprocess(cls, tasks, func, Q):
        rs = func(tasks)
        if Q is None:
            return rs
        else:
            Q.put(rs)

class Z3(object):
    def __init__(self):
        self.solver = z3.Solver()
        self.solver.set("timeout", 500)

    def solve(self, f):
        self.solver.push()
        self.solver.add(f)
        try:
            r = self.solver.check()
            if r == z3.unsat:
                return Ternary(False)
            elif r == z3.sat:
                # m = self.solver.model()
                return Ternary(True)
            else:
                return Ternary(None) # unknown
        except:
            return Ternary(None)
        finally:
            self.solver.pop()

class List(object):
    @classmethod
    def flatten(self, l):
        return [item for sublist in l for item in sublist]

    @classmethod
    def remove_dups(self, l):
        return list(set(l))

    @classmethod
    def add_lst_dict(self, d, k, v):
        if k in d:
            d[k].append(v)
        else:
            d[k] = [v]

    @classmethod
    def group_by(self, func, ls):
        grouped = {}
        for elem in ls:
            key = func(elem)
            grouped.setdefault(key, []).append(elem)
        return grouped

    @classmethod
    def partition(self, pred, ls):
        p, np = [], []
        for elem in ls:
            if pred(elem):
                p.append(elem)
            else:
                np.append(elem)
        return p, np

    @classmethod
    def all_subsets(self, ls):
        ss = chain(*map(lambda x: combinations(ls, x),
                        range(0, len(ls)+1)))
        return map(lambda s: list(s), list(ss))

    @classmethod
    def all_is_identical(self, ls):
        # return ls[1:] == ls[:-1]
        return ls.count(ls[0]) == len(ls)

class Const(object):
    nil_addr = 0
    fresh_vars_dummy_addr = -1
    fid = 0
    res = 'res'

    @classmethod
    def mk_fresh(self):
        self.fid = self.fid + 1
        return self.fid

