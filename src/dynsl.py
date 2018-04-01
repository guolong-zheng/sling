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
       dest='pre', nargs='*',
       type=int)

    ag('--post', '-post',
       dest='post', nargs='*',
       type=int)

    ag('--inv', '-inv',
       dest='inv', nargs='*',
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
        inv_bps = args.inv
        size = args.size
        pred_file = args.pred
        pred_defn = pred_file.read()

        trace_pairs, inv_traces = get_traces(infile, pre_bps, post_bps, inv_bps, size)
        # debug(trace_pairs)

        if trace_pairs:
            pre_traces, post_traces = zip(*trace_pairs)
        else:
            pre_traces, post_traces = [], []

        # debug(pre_traces)
        # debug(post_traces)
        # debug(inv_traces)

        pre_locs = List.remove_dups(map(lambda pr: pr.loc, pre_traces))
        post_locs = List.remove_dups(map(lambda po: po.loc, post_traces))
        inv_locs = List.remove_dups(map(lambda inv: inv.loc, inv_traces))

        pre_post_pairs = map(lambda (pr, po): ((pr.loc, pr.id),
                                               (po.loc, po.id)), trace_pairs)
        # debug(pre_post_pairs)

        pre_post_dict = {}
        for ((pr_loc, pr_id), (po_loc, po_id)) in pre_post_pairs:
            # if pr_loc not in pre_post_dict:
            #     pdict = {}
            #     pdict[po_loc] = [(pr_id, po_id)]
            #     pre_post_dict[pr_loc] = pdict
            # else:
            #     pdict = pre_post_dict[pr_loc]
            #     if po_loc not in pdict:
            #         pdict[po_loc] = [(pr_id, po_id)]
            #     else:
            #         pdict[po_loc].append((pr_id, po_id))
            pdict = pre_post_dict.setdefault(pr_loc, {})
            pairs = pdict.setdefault(po_loc, [])
            pairs.append((pr_id, po_id))
        # debug(pre_post_dict)

        seplogic_parser = SepLogicParser()
        defn_ast = seplogic_parser.defn_parser.parse(pred_defn)
        prog = seplogic_parser.transform(defn_ast)

        type_infer = TInfer()
        tprog = type_infer.infer(prog)
        debug(tprog)

        pre_models = TModel.make_lst(pre_traces, tprog)
        post_models = TModel.make_lst(post_traces, tprog)
        inv_models = TModel.make_lst(inv_traces, tprog)

        rdict = {}
        grp_models = List.group_by(lambda model: model.loc,
                                   pre_models + post_models + inv_models)
        for loc in grp_models:
            debug('Inferring ' + ('pre-' if loc in pre_locs else
                                  ('post-' if loc in post_locs else 'inv-')) +
                  'conditions at the location ' + str(loc) + ' ...\n')
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
            # debug(map(lambda (f, _): f, f_residue_lst))
            rdict[loc] = f_residue_dict

        # debug(rdict)

        for pr_loc in pre_locs:
            pr_po_pairs = pre_post_dict[pr_loc]
            pr_residue_lst = rdict[pr_loc]
            for (pr_f, pr_residue) in pr_residue_lst:
                # debug(pr_f)
                pr_f_posts = {}
                for po_loc in pr_po_pairs:
                    pairs = pr_po_pairs[po_loc]
                    # debug(pairs)
                    po_residue_lst = rdict[po_loc]
                    for (po_f, po_residue) in po_residue_lst:
                        # debug(po_f)
                        if all(pr_residue[pr_id].is_same_heap_dom(po_residue[po_id])
                               for (pr_id, po_id) in pairs):
                            pr_f_posts.setdefault(po_loc, []).append(po_f)
                        else:
                            # debug(pr_residue[pr_id])
                            # debug(po_residue[po_id])
                            pass
                if len(pr_f_posts) == len(pr_po_pairs):
                    debug('==============================')
                    debug('Precondition at location ' + str(pr_loc) + ':')
                    debug(pr_f)
                    debug('Corresponding postconditions:')
                    for po_loc in pr_f_posts:
                        po_f_lst = pr_f_posts[po_loc]
                        debug('Postconditions at location ' + str(po_loc) + ':')
                        for po_f in po_f_lst:
                            debug(po_f)

        # debug(inv_models)
        for inv_loc in inv_locs:
            inv_residue_lst = rdict[inv_loc]
            debug('Invariants at location ' + str(inv_loc) + ':')
            for (inv, inv_residue) in inv_residue_lst:
                debug(inv)
                # debug(inv_residue)

    else:
        debug('Inside test mode')
        test()

if __name__ == "__main__":
    main()
