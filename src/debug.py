from inspect import getframeinfo, stack
from printer import *
import ntpath

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def debug(obj):
    message = Printer.str_of(obj)
    caller = getframeinfo(stack()[1][0])
    print "%s:%d - %s" % (path_leaf(caller.filename),
                          caller.lineno,
                          message)
