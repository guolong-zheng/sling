from seplogic import *
from trace import *
from parser import *
from iincr import *
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

        pre_models = Traces.mk_model_lst(pre_traces, tprog)
        post_models = Traces.mk_model_lst(post_traces, tprog)

        fdict = {}
        grp_models = List.group_by(lambda (loc, model): loc,
                                   pre_models + post_models)
        for loc in grp_models:
            models = map(lambda (loc, model): model, grp_models[loc])
            fs = IIncr.infer(tprog, models)
            fdict[loc] = fs
        # debug(fdict)

        # for ((pr_loc, pr_model), (po_loc, po_model)) in zip(pre_models, post_models):
        #     pr_fs = fdict[pr_loc]
        #     po_fs = fdict[po_loc]
        #     pre_ctx_lst = []
        #     for pr_f in pr_fs:
        #         pr_rctx = pr_model.get_residue_ctx(pr_f)
        #         if pr_rctx:
        #             pre_ctx_lst.extend(map(lambda rctx: (pr_f, rctx), pr_rctx))
        #     # debug(pre_ctx_lst)

        #     for po_f in po_fs:
        #         po_rctx = po_model.get_residue_ctx(po_f)
        #         # debug(po_rctx)
    else:
        debug('Inside test mode')
        test()

if __name__ == "__main__":
    main()
