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
    # debug(traces)

    pred_file = args.pred
    pred_defn = pred_file.read()

    seplogic_parser = SepLogicParser()
    defn_ast = seplogic_parser.defn_parser.parse(pred_defn)
    prog = seplogic_parser.transform(defn_ast)

    type_infer = TInfer()
    tprog = type_infer.infer(prog)
    debug(tprog)

    for pos in traces:
        trace_lst = traces[pos]
        debug(pos)
        # debug(trace_lst)
        model_lst = []
        for trace in trace_lst:
            s = trace.stack
            h = trace.heap
            model = SHModel(s, h, tprog)
            model_lst.append(model)
        debug(model_lst)
        fs = SLInfer.infer_location(tprog, model_lst)

    # test()

if __name__ == "__main__":
    main()
