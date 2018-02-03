import sys
sys.path.append("/Applications/Xcode.app/Contents/SharedFrameworks/LLDB.framework/Resources/Python")
import lldb
import os

class Field(object):
    pass

class PtrField(Field):
    def __init__(self, name, addr):
        self.name = name
        self.data = addr

    def __str__(self):
        return self.name + '=' + str(self.data)

class DataField(Field):
    def __init__(self, name, data):
        self.name = name
        self.data = data

    def __str__(self):
        return self.name + '=' + self.data

class Trace(object):
    def __init__(self, root, fields):
        self.root = root
        self.fields = fields

    def __str__(self):
        return str(self.root) + '<' + (', '.join(map(str, self.fields))) + '>'


#def getTrace(file):
if True:
	# Set the path to the executable to debug
	exe = "/Users/guolongzheng/sl/seplogic-dynamic/test/test"

	debugger = lldb.SBDebugger.Create()
	debugger.SetAsync (False)

	# Create a target from a file and arch
	target = debugger.CreateTargetWithFileAndArch (exe, lldb.LLDB_ARCH_DEFAULT)

	if target:
		# If the target is valid set a breakpoint at main
		main_bp = target.BreakpointCreateByLocation ("/Users/guolongzheng/sl/seplogic-dynamic/test/test.c", 23);
		print("Created a breakpoint at:{}").format(main_bp)

	# Launch the process 
		process = target.LaunchSimple (None, None, os.getcwd())
		state = process.GetState ()	
		if state == lldb.eStateStopped:
		       	thread = process.GetThreadAtIndex (0)
			frame = thread.GetFrameAtIndex (0)
			if frame:
				# Retieve information of all visible variables in the frame
				vars = frame.GetVariables(True, True, True, True)
				traces = []
				for var in vars:
                                    if var.TypeIsPointerType():
                                        root = var.GetAddress()
                                        fields = []
                                       
                                        for i in range(0, var.GetNumChildren()):
                                            child = var.GetChildAtIndex(i)
                                            if child.TypeIsPointerType():
                                                ptr = PtrField(child.GetName(),child.GetAddress())
                                            else:
                                                ptr = DataField(child.GetName(),child.GetValue())
                                           
                                            fields.append(ptr)
                                        traces.append(Trace(root,fields))
			print map(str,traces)
		    
