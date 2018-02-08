import sys
sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os
from trace import *
import pdb

def create_target(exe, bp_list):
    os.chdir(os.getcwd()+"/test")
    debugger = lldb.SBDebugger.Create()
    debugger.SetAsync(False)
    target = debugger.CreateTargetWithFileAndArch (exe, lldb.LLDB_ARCH_DEFAULT)

    if target:
        for bp in bp_list:
            main_bp = target.BreakpointCreateByLocation(exe+".c", bp)
            #print "break point created at : %s " % main_bp
    else:
        print "Can't create debugger instance"

    return target

#to do, add input parameter to reuse target
def get_model(target):
    process = target.LaunchSimple (None, None, os.getcwd())
    state = process.GetState()
    if state == lldb.eStateStopped:
        thread = process.GetThreadAtIndex (0)
        frame = thread.GetFrameAtIndex (0)
        if frame:
            vars = frame.GetVariables(True, True, True, True)
            stack, heap = traverse_heap(vars)
    else:
        print "No breakpoint set up!"
    return stack, heap

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
            return
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

    for i in heap:
        print heap[i]
    return heap, to_visit

def main():
    exe = 'test'
    bp_list = [23]

    target = create_target(exe, bp_list)
    (s, heap) = get_model(target)


if __name__ == "__main__":
    main()
