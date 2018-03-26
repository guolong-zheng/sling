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
        pred_file = args.pred
        pred_defn = pred_file.read()

        trace_pairs = get_traces(infile, pre_bps, post_bps, size)
        pre_traces, post_traces = zip(*trace_pairs)

        pre_locs = List.remove_dups(map(lambda pr: pr.loc, pre_traces))
        post_locs = List.remove_dups(map(lambda po: po.loc, post_traces))

        pre_post_pairs = map(lambda (pr, po): ((pr.loc, pr.id),
                                               (po.loc, po.id)), trace_pairs)
        # debug(pre_post_pairs)

        pre_post_dict = {}
        for ((pr_loc, pr_id), (po_loc, po_id)) in pre_post_pairs:
            if pr_loc not in pre_post_dict:
                pdict = {}
                pdict[po_loc] = [(pr_id, po_id)]
                pre_post_dict[pr_loc] = pdict
            else:
                pdict = pre_post_dict[pr_loc]
                if po_loc not in pdict:
                    pdict[po_loc] = [(pr_id, po_id)]
                else:
                    pdict[po_loc].append((pr_id, po_id))
        debug(pre_post_dict)

        seplogic_parser = SepLogicParser()
        defn_ast = seplogic_parser.defn_parser.parse(pred_defn)
        prog = seplogic_parser.transform(defn_ast)

        type_infer = TInfer()
        tprog = type_infer.infer(prog)
        debug(tprog)

        pre_models = TModel.make_lst(pre_traces, tprog)
        post_models = TModel.make_lst(post_traces, tprog)

        rdict = {}
        grp_models = List.group_by(lambda model: model.loc,
                                   pre_models + post_models)
        for loc in grp_models:
            models = grp_models[loc]
            f_residue_lst = IIncr.infer(tprog, models)

            def mk_mdict(models):
                mdict = {}
                for model in models:
                    mdict[model.id] = model
                return mdict

            f_residue_dict = map(lambda (f, residue_model):
                                 (f, mk_mdict(residue_model)),
                                 f_residue_lst)
            rdict[loc] = f_residue_dict

        # debug(rdict)

        for pr_loc in pre_locs:
            pr_po_pairs = pre_post_dict[pr_loc]
            pr_residue_lst = rdict[pr_loc]
            for (pr_f, pr_residue) in pr_residue_lst:
                debug(pr_f)
                pr_f_posts = {}
                for po_loc in pr_po_pairs:
                    pairs = pr_po_pairs[po_loc]
                    po_residue_lst = rdict[po_loc]
                    for (po_f, po_residue) in po_residue_lst:
                        if all(pr_residue[pr_id].is_same_heap_dom(po_residue[po_id])
                               for (pr_id, po_id) in pairs):
                            debug(po_loc)
                            debug(po_f)


    else:
        debug('Inside test mode')
        test()

if __name__ == "__main__":
    main()
