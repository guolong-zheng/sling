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

    ag('--pre', '-pre',
       dest='pre', nargs='+',
       type=int)

    ag('--post', '-post',
       dest='post', nargs='+',
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

    ag('--test', '-test',
       action="store_true")

    args = aparser.parse_args()

    import settings
    settings.doMP = args.mp
    settings.print_type = not args.notype
    settings.test_mode = args.test

    if not settings.test_mode:
        infile = args.infile
        pre_bps = args.pre
        post_bps = args.post
        size = args.size

        trace_pairs = get_traces(infile, pre_bps, post_bps, size)
        pre_traces, post_traces = zip(*trace_pairs)
        # debug(pre_traces)
        # debug(post_traces)

        pred_file = args.pred
        pred_defn = pred_file.read()

        seplogic_parser = SepLogicParser()
        defn_ast = seplogic_parser.defn_parser.parse(pred_defn)
        prog = seplogic_parser.transform(defn_ast)

        type_infer = TInfer()
        tprog = type_infer.infer(prog)
        debug(tprog)

        def infer_traces(traces):
            models = []
            for trace in traces:
                s = trace.stack
                h = trace.heap
                model = SHModel(s, h, tprog)
                models.append(model)
            fs = SLInfer.infer_location(tprog, models)
            return fs

        pre_conds = infer_traces(pre_traces)

        grp_post_traces = List.group_by(lambda t: t.loc, post_traces)
        for loc in grp_post_traces:
            loc_post_conds = infer_traces(grp_post_traces[loc])
    else:
        debug('Inside test mode')
        test()

if __name__ == "__main__":
    main()
