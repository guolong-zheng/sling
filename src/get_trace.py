import sys
#sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os
from collections import defaultdict
from trace import *
from debug import *

def create_target(exe, bps):
    #os.chdir(os.getcwd()+"/simple_example/sll")
    exe = os.path.join(os.getcwd(), exe)
    debugger = lldb.SBDebugger.Create()
    debugger.SetAsync(False)
    target = debugger.CreateTargetWithFileAndArch(exe, lldb.LLDB_ARCH_DEFAULT)
    if target:
        for bp in bps:
            target.BreakpointCreateByLocation(exe+".c", bp)
    else:
        print "Can't create debugger instance"

    return target

def get_model(target, size):
    process = target.LaunchSimple(None, [size], os.getcwd())
    traces = defaultdict(list)
    state = process.GetState()
    thread = process.GetThreadAtIndex (0)
    # stoped due to break point
    while thread.GetStopReason() == lldb.eStopReasonBreakpoint:
        frame = thread.GetFrameAtIndex (0)
        location = frame.GetLineEntry().GetLine()
        if frame:
            vars = frame.GetVariables(True, True, True, True)
            stack, heap = traverse_heap(vars)
            traces[location].append(Traces(location, stack, heap))
        process.Continue()
    # print "No breakpoint set up!"
    return traces

def traverse_heap(vars):
    stack = {}
    heap = {}
    # store vars in heap that needed to be traversed
    to_visit = []
    for var in vars:
        if var.TypeIsPointerType():
            stack[var.GetName()] = StackTrace(var.GetName(), Addr(var.GetValue()))
            to_visit.append(var)
        elif var.GetValue() is not None:
            stack[var.GetName()] = StackTrace(var.GetName(), Int(var.GetValue()))

    heap = expand_cell(heap, to_visit)

    return stack, heap

def expand_cell(heap, to_visit):
    #pdb.set_trace()
    while len(to_visit) != 0:
        var = to_visit.pop(0)
        if var.TypeIsPointerType() and var.GetValueAsUnsigned() == 0:
            continue
        typ = str_type(var.GetType().GetCanonicalType())
        var = var.Dereference()
        heap_addr = str(var.GetAddress())

        if heap_addr.startswith('0x') and heap_addr not in heap:
            fields = []
            for i in range(0, var.GetNumChildren()):
                child = var.GetChildAtIndex(i)
                child_typ = str_type(child.GetType().GetCanonicalType())
                child_name = child.GetName()
                if child.TypeIsPointerType():
                    if child.GetValueAsUnsigned() == 0:
                        field = PtrField(child_name, Addr(None))
                    else:
                        field = PtrField(child_name, Addr(str(child.GetValue())))
                        to_visit.append(child)
                else:
                    field = DataField(child_name, Int(child.GetValue()))

                fields.append(field)

            heap[heap_addr] = HeapTrace(Addr(heap_addr), typ, fields)

    return heap


def get_traces(input, bps, size):
    target = create_target(input, bps)
    traces = {}
    for s in size:
        model = get_model(target, s)
        debug(model)
        traces.update(model)
    return traces


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

def main():
    exe = "simple_example/GRASShopper/dl_concat"
    bps = [46, 48, 56, 63]

    target = create_target(exe, bps)
    traces = get_model(target, '5')
    # print traces_str(traces)
    write_file(exe, traces)

if __name__ == "__main__":
    main()
