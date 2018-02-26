import sys
#sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os
from collections import defaultdict
from trace import *

def create_target(exe, bps):
    os.chdir(os.getcwd()+"/simple_example")
    debugger = lldb.SBDebugger.Create()
    debugger.SetAsync(False)
    target = debugger.CreateTargetWithFileAndArch (exe, lldb.LLDB_ARCH_DEFAULT)

    if target:
        for bp in bps:
            target.BreakpointCreateByLocation(exe+".c", bp)
            #print "break point created at : %s " % main_bp
    else:
        print "Can't create debugger instance"

    return target

def get_model(target):
    process = target.LaunchSimple (None, None, os.getcwd())
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
        else:
            stack[var.GetName()] = StackTrace(var.GetName(), Int(var.GetValue()))

    heap = expand_cell(heap, to_visit)

    return stack, heap

def expand_cell(heap, to_visit):
    #pdb.set_trace()
    while len(to_visit) != 0:
        var = to_visit.pop(0)
        if var.TypeIsPointerType() and var.GetValueAsUnsigned() == 0:
            continue
        typ = var.GetType()
        var = var.Dereference()
        heap_addr = str(var.GetAddress())

        if heap_addr not in heap:
            fields = []
            for i in range(0, var.GetNumChildren()):
                child = var.GetChildAtIndex(i)
                if child.TypeIsPointerType():
                    if child.GetValueAsUnsigned() == 0:
                        field = PtrField(child.GetName(), Addr(None))
                    else:
                        field = PtrField(child.GetName(),Addr(str(child.GetValue())))
                        to_visit.append(child)
                else:
                    field = DataField(child.GetName(),Int(child.GetValue()))

                fields.append(field)

            heap[heap_addr] = HeapTrace(Addr(heap_addr), str(typ), fields)

    return heap


def get_traces(input, bps):
    target = create_target(input, bps)
    traces = get_model(target)

    return traces

def main():
    exe = "test"
    bps = [37,39,47,54]

    target = create_target(exe, bps)
    traces = get_model(target)

if __name__ == "__main__":
    main()
