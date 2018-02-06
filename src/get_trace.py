import sys
sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os
from trace import *

def create_target(file, bp_list):
    debugger = lldb.SBDebugger.Create()
    debugger.SetAsync(False)
    target = debugger.CreateTargetWithFileAndArch (file, lldb.LLDB_ARCH_DEFAULT)

    if target:
        for bp in bp_list:
            target.BreakpointCreateByLocation(file, bp)
    else:
        print "Can't create debugger instance"

    return target

def get_model(target, input):
    process = target.LaunchSimple (input, None, os.getcwd())
    visited = []
    state = process.GetState ()
    if state == lldb.eStateStopped:
        thread = process.GetThreadAtIndex (0)
        frame = thread.GetFrameAtIndex (0)
        if frame:
            vars = frame.GetVariables(True, True, True, True)
            stack, heap = traverse_heap(vars)

def traverse_heap(vars):
    stack = {}
    heap = {}

    # store vars in heap that needed to be traversed
    to_visit = []

    for var in vars:
        stack[var.GetName()] = StackVar(var.GetName(), var.GetType(), var.GetValue())
        if var.TypeIsPointerType():
            to_visit.append(var)

    heap = expand_cell(heap, to_visit)

    return stack, heap

def expand_cell(heap, to_visit):
    while len(to_visit) != 0:
        var = to_visit.pop(0)
        root = var.GetAddress()
        if root not in heap:
            fields = []
            for i in range(0, var.GetNumChildren()):
                child = var.GetChildAtIndex(i)
                if child.TypeIsPointerType():
                    ptr = PtrField(child.GetName(),child.GetAddress())
                    to_visit += child.GetAddress()
                else:
                    ptr = DataField(child.GetName(),child.GetValue())
                fields.append(ptr)
            heap[root] = HeapCell(root, fields)
    return heap
