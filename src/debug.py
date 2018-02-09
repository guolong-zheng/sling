from inspect import getframeinfo, stack
import ntpath

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def debug(message):
    caller = getframeinfo(stack()[1][0])
    print "%s:%d - %s" % (path_leaf(caller.filename), caller.lineno, message)
