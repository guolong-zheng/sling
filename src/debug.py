from inspect import getframeinfo, stack
import printer
import ntpath

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

def debug(message):
    if isinstance(message, list):
        message = printer.str_of_list(message, str)
    if isinstance(message, tuple):
        s = ''
        for m in message:
            s = s + str(m)
        message = s
    caller = getframeinfo(stack()[1][0])
    print "%s:%d - %s" % (path_leaf(caller.filename),
                          caller.lineno,
                          message)
