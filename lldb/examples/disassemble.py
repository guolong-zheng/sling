#!/usr/bin/python

import lldb
import os

def disassemble_instructions(insts):
    for i in insts:
        print i

# Set the path to the executable to debug
exe = "./dictionary"

# Create a new debugger instance
debugger = lldb.SBDebugger.Create()

# When we step or continue, don't return from the function until the process 
# stops. Otherwise we would have to handle the process events ourselves which, while doable is
#a little tricky.  We do this by setting the async mode to false.
debugger.SetAsync (False)

# Create a target from a file and arch
print "Creating a target for '%s'" % exe

target = debugger.CreateTargetWithFileAndArch (exe, lldb.LLDB_ARCH_DEFAULT)

if target:
    # If the target is valid set a breakpoint at main
    main_bp = target.BreakpointCreateByName ("populate_dictionary", target.GetExecutable().GetFilename());

    print main_bp

    # Launch the process. Since we specified synchronous mode, we won't return
    # from this function until we hit the breakpoint at main
    process = target.LaunchSimple (["./story.txt"], None, os.getcwd())

    print 'after LaunchSimple'

    # Make sure the launch went ok
    if process:
        # Print some simple process info
        state = process.GetState ()
        print process
        if state == lldb.eStateStopped:
            # Get the first thread
            thread = process.GetThreadAtIndex (0)
            if thread:
                # Print some simple thread info
                print thread
                # Get the first frame
                frame = thread.GetFrameAtIndex (0)
                if frame:
                    # Print some simple frame info
                    print frame

                    function = frame.GetFunction()
                    # See if we have debug info (a function)

                    if function:
                        # We do have a function, print some info for the function
                        # print function
                        # Now get all instructions for this function and print them
                        # insts = function.GetInstructions(target)
                        # disassemble_instructions (insts)
                        vars = frame.GetVariables(True, False, False, False)
                        print vars

                        # end_addr = frame.GetLineEntry().GetEndAddress()
                        # end_bp = target.BreakpointCreateBySBAddress(end_addr)
                        end_bp = target.BreakpointCreateByLocation(
						    frame.GetLineEntry().GetFileSpec(), 101)
                        print end_bp

                        line_num = frame.GetLineEntry().GetLine()
                        print line_num

                        process.Continue()
                    else:
                        # See if we have a symbol in the symbol table for where we stopped
                        symbol = frame.GetSymbol();
                        if symbol:
                            # We do have a symbol, print some info for the symbol
                            print symbol
