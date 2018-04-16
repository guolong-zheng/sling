import sys
#sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os
from collections import defaultdict
from trace import *
from debug import *
from model import *

def create_target(exe, bps):
    exe = os.path.join(os.getcwd(), exe)
    debugger = lldb.SBDebugger.Create()
    debugger.SetAsync(False)
    target = debugger.CreateTargetWithFileAndArch(exe, lldb.LLDB_ARCH_DEFAULT)
    ldict = {}
    if target:
        for loc in bps:
            bp = target.BreakpointCreateByLocation(exe+".c", loc)
            bp_loc = bp.GetLocationAtIndex(0)
            bp_line = bp_loc.GetAddress().GetLineEntry().GetLine()
            ldict[loc] = bp_line
    else:
        print "Can't create debugger instance"

    return target, ldict

def get_model(target, pre_locs, post_locs, inv_locs, size):
    process = target.LaunchSimple([size], None, os.getcwd())
    state = process.GetState()
    thread = process.GetThreadAtIndex(0)
    pre_traces = []
    post_traces = []
    inv_traces = []
    # stoped due to break point
    while thread.GetStopReason() == lldb.eStopReasonBreakpoint:
        frame = thread.GetFrameAtIndex(0)
        location = frame.GetLineEntry().GetLine()
        if frame:
            if location in pre_locs:
                # Do not get local variables in the precondition inference
                vars = frame.GetVariables(True, False, True, True)
            else:
                vars = frame.GetVariables(True, True, True, True)
            # debug(vars)
            stack, heap = traverse_heap(vars)
            trace = Traces(location, stack, heap)
            if location in pre_locs:
                pre_traces.append(trace)
            elif location in post_locs:
                thread.StepOut()
                ret = thread.GetStopReturnValue()
                if ret:
                    if ret.TypeIsPointerType():
                        val = Addr(ret.GetValue())
                    else:
                        val = Int(ret.GetValue())
                    trace.ret = val
                post_traces.append(trace)
            else:
                inv_traces.append(trace)
        process.Continue()
    # print "No breakpoint set up!"
    # debug(pre_traces)
    # debug(post_traces)
    # debug(inv_traces)
    return (pre_traces, post_traces, inv_traces)

def traverse_heap(vars):
    stack = Stack()
    heap = Heap()
    # store vars in heap that needed to be traversed
    to_visit = []
    for var in vars:
        if var.GetValue() is not None:
            if var.TypeIsPointerType():
                stack.add(var.GetName(), Addr(var.GetValue()))
                to_visit.append(var)
            else:
                stack.add(var.GetName(), Int(var.GetValue()))

    heap = expand_cell(heap, to_visit)

    return stack, heap

def expand_cell(heap, to_visit):
    #pdb.set_trace()
    while to_visit:
        var = to_visit.pop(0)
        if var.TypeIsPointerType() and var.GetValueAsUnsigned() == 0:
            continue
        typ = str_type(var.GetType().GetCanonicalType())
        var = var.Dereference()
        heap_addr = int(var.GetAddress())

        if heap_addr not in heap:
            fields = []
            for i in range(0, var.GetNumChildren()):
                child = var.GetChildAtIndex(i)
                child_typ = str_type(child.GetType().GetCanonicalType())
                child_name = child.GetName()
                if child.TypeIsPointerType():
                    if child.GetValueAsUnsigned() == 0:
                        field = PtrField(child_name, Addr(Const.nil_addr))
                    else:
                        field = PtrField(child_name, Addr(child.GetValue()))
                        to_visit.append(child)
                else:
                    field = DataField(child_name, Int(child.GetValueAsSigned()))

                fields.append(field)

            heap.add(heap_addr, (typ, fields))

    return heap


def get_traces(input, pre_bps, post_bps, inv_bps, size):
    target, ldict = create_target(input, pre_bps + post_bps + inv_bps)
    pre_locs = map(lambda l: ldict[l], pre_bps)
    post_locs = map(lambda l: ldict[l], post_bps)
    inv_locs = map(lambda l: ldict[l], inv_bps)
    trace_pairs = []
    for s in size:
        (pre_traces, post_traces, inv_traces) = get_model(target, pre_locs, post_locs, inv_locs, s)
        trace_pairs.extend(zip(pre_traces[::-1], post_traces))
    return trace_pairs, inv_traces

def str_type(typ):
    typ_str = str(typ).replace("struct",'')
    typ_str = typ_str.translate(None, '*').strip()

    return typ_str

def write_file(exe, traces):
    for loc in traces:
        tr = traces[loc]
        for x in tr:
            count = str(tr.index(x))
            filename = exe.split("/")[-1] + "_" + str(loc) + "_" + count + ".txt"
            path = os.getcwd() + "/traces/trace5"
            fw = open(os.path.join(path, filename), "w+")
            st = x.stack
            hp = x.heap
            for s in st:
                "writing stack"
                fw.write(str(st[s]) + ";\n")
            for h in hp:
                "writing heap"
                fw.write(str(hp[h]) + ";\n")
            fw.close()

def traces_str(traces):
    for t in traces:
        print "trace at location: %s" % t
        tr = traces[t]
        for x in tr:
            st = x.stack
            hp = x.heap
            print "stack is:"
            for s in st:
                print st[s]
            print "heap is:"
            for h in hp:
                print hp[h]

# def main():
#     exe = "simple_example/GRASShopper/dl_concat"
#     bps = [46, 48, 56, 63]

#     target = create_target(exe, bps)
#     traces = get_model(target, '5')
#     # print traces_str(traces)
#     write_file(exe, traces)

# if __name__ == "__main__":
#     main()
