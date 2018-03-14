from seplogic import *
from trace import *
from parser import *
from debug import *
from typ import *
from get_trace import *
from test import *
import argparse

def main():
    aparser = argparse.ArgumentParser(description='SLING')
    ag = aparser.add_argument

    ag('--input', '-input',
       dest='infile')

    ag('--breaks', '-breaks',
        dest='breaks', nargs='+',
        type=int)

    ag('--size', '-size',
        dest='size', nargs='+')

    ag('--trace', '-trace',
       dest='trace', type=open)

    ag('--def', '-def',
       dest='pred', type=open)

    ag('--mp', '-mp',
       action="store_true")

    ag('--notype', '-notype',
       action="store_true")

    args = aparser.parse_args()

    import settings
    settings.doMP = args.mp
    settings.print_type = not args.notype

    infile = args.infile
    bps = args.breaks
    size = args.size

    traces = get_traces(infile, bps, size)
    debug(traces)
    
    # for t in traces:
    #     print "trace at location: %s" % t
    #     tr = traces[t]
    #     for x in tr:
    #         st = x.stack
    #         hp = x.heap
    #         print "stack is:"
    #         for s in st:
    #             print st[s]
    #         print "heap is:"
    #         for h in hp:
    #             print hp[h]

    defn = args.pred
    traces = args.trace

    test()

if __name__ == "__main__":
    main()
