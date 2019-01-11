from seplogic import *
from trace import *
from parser import *
from iincr import *
from debug import *
from typ import *
from get_trace import *
from test import *
import argparse
import timeit
import re

def normalize(inv):
    regex = re.compile('fv![0-9]+')
    match = regex.findall(inv)
    i = 0
    for x in match:
        inv = inv.replace(x, "fv"+str(i))
        i = i + 1
    return inv

def remove_redundent(inv_set):
    new_set = set()
    #regex = re.compile('fv![0-9]+')
    for inv in inv_set:
        #match = regex.findall(inv)
        #i = 0
        #for x in match:
        #    inv = inv.replace(x, "fv"+str(i))
        #    i = i + 1
        new_set.add(normalize(inv))
    return new_set


def main():
    aparser = argparse.ArgumentParser(description='SLING')
    ag = aparser.add_argument
    
    ag('--java', '-java',
       action="store_true")
       
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

    ag('--stats', '-stats',
       action="store_true")

    args = aparser.parse_args()

    import settings
    settings.doMP = args.mp
    settings.print_type = not args.notype
    settings.test_mode = args.test
    settings.stats_mode = args.stats

    stat_locs = 0
    stat_traces = 0
    stat_preds = 0
    stat_specs = 0
    stat_invs = 0
    stat_free_vars = 0
    stat_atom_data = 0
    stat_atom_pred = 0
    stat_pure_constrs = 0
    stat_time = 0

    if not settings.test_mode:
        infile = args.infile
        pre_bps = args.pre
        post_bps = args.post
        inv_bps = args.inv
        size = args.size
        pred_file = args.pred
        pred_defn = pred_file.read()

        start_time = timeit.default_timer()

        if args.java:
            trace_pairs, inv_traces = get_traces_from_file(infile, pre_bps, post_bps, inv_bps)
        else:
            trace_pairs, inv_traces = get_traces(infile, pre_bps, post_bps, inv_bps, size)

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
        # debug(tprog)

        stat_preds = len(tprog.pred_defn_lst)

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
            # debug(models)
            # debug(map(lambda (f, _): f, f_residue_lst))

            def mk_mdict(models):
                mdict = {}
                for model in models:
                    mdict[model.id] = model
                return mdict

            f_residue_dict = map(lambda (f, residue_model):
                                 (f, mk_mdict(residue_model)),
                                 f_residue_lst)
            #debug(map(lambda (f, _): f, f_residue_lst))
            rdict[loc] = f_residue_dict

        pre_num = 0
        post_num = 0
        loop_num = 0
        for pr_loc in pre_locs:
            pr_po_pairs = pre_post_dict[pr_loc]
            pr_residue_lst = rdict[pr_loc]
            
            pr_f_posts = {}
            pre_invs = {}
            for (pr_f, pr_residue) in pr_residue_lst:
                # debug(pr_f)
                pre_invs.setdefault(pr_loc,[]).append(pr_f)
                for po_loc in pr_po_pairs:
                    pairs = pr_po_pairs[po_loc]
                    # debug(pairs)
                    po_residue_lst = rdict[po_loc]
                    for (po_f, po_residue) in po_residue_lst:
                        # debug(po_f)
                        #if all(pr_residue[pr_id].is_same_heap_dom(po_residue[po_id])
                        #       for (pr_id, po_id) in pairs):
                            pr_f_posts.setdefault(po_loc, []).append(po_f)
                        #else:
                            # for (pr_id, po_id) in pairs:
                            #     prr = pr_residue[pr_id]
                            #     por = po_residue[po_id]
                            #     if not prr.is_same_heap_dom(por):
                            #         debug(pr_f)
                            #         debug(prr)
                            #         debug(po_f)
                            #         debug(por)
                            pass
                                #if len(pr_f_posts) == len(pr_po_pairs):
            debug('==============================')
            debug('Precondition at location ' + str(pr_loc) + ':')
            #debug(pr_f)
            for pre_loc in pre_invs:
                pre_f_lst = pre_invs[pre_loc]
                pre_f_lst = remove_redundent(set(map(str,pre_f_lst)))
                #debug('Precondition at location ' + str(pr_loc) + ':')

                for pre_f in pre_f_lst:
                    pre_num = pre_num + 1
                    debug(pre_f)
            # stat_specs = stat_specs + 1
            debug('Corresponding postconditions:')
            #specs_num = 1
            for po_loc in pr_f_posts:
                po_f_lst = pr_f_posts[po_loc]
		po_f_lst = remove_redundent(set(map(str,po_f_lst)))
                debug('Postconditions at location ' + str(po_loc) + ':')
                #debug(specs_num)
                for po_f in po_f_lst:
                    #specs_num = specs_num + 1
                    post_num = post_num + 1
                    debug(po_f)
            stat_specs += (post_num + pre_num)
                #debug('==============================')

        # debug(inv_models)
        for inv_loc in inv_locs:
            inv_residue_lst = rdict[inv_loc]
            debug('Invariants at location ' + str(inv_loc) + ':')
            loop_inv_set = []
            for (inv, inv_residue) in inv_residue_lst:
                if normalize(str(inv)) in loop_inv_set:
                    pass
                else:
                    loop_inv_set.append(str(inv))
                    debug(inv)
                    loop_num = loop_num + 1
        stat_specs += loop_num
                # debug(inv_residue)
        debug('==============================')

        stat_time = timeit.default_timer() - start_time
        stat_locs = len(pre_locs) + len(post_locs) + len(inv_locs)
        stat_traces = len(pre_models) + len(post_models) + len(inv_models)

        inv_set = []
        for loc in rdict:
            res_lst = rdict[loc]
            #debug(res_lst)
            stat_invs += len(res_lst)
            for (inv, _) in res_lst:
                if normalize(str(inv)) in inv_set:
                    pass
                else:
                    #debug(inv)
                    inv_set.append(str(inv))
                    inv_atom_data, inv_atom_pred = inv.stat_atomic_preds()
                    stat_atom_data += inv_atom_data
                    stat_atom_pred += inv_atom_pred
                    stat_pure_constrs += inv.stat_pure_constrs()
                    stat_free_vars += len(inv.fv())

        debug('Number of locations: ' + str(stat_locs))
        debug('Number of traces: ' + str(stat_traces))
        debug('Number of pre-defined predicates: ' + str(stat_preds))
        debug('Number of inferred assertions: ' + str(stat_invs))
        debug('Number of free variables: ' + str(stat_free_vars))
        debug('Number of atomic singleton predicates: ' + str(stat_atom_data))
        debug('Number of atomic inductive predicates: ' + str(stat_atom_pred))
        debug('Number of pure constraints: ' + str(stat_pure_constrs))
        debug('Number of total invs: ' + str(stat_specs))
        debug('Number of pres:' + str(pre_num))
        debug('Number of post:' + str(post_num))
        debug('Number of loop:' + str(loop_num))
        debug('Running time (sec): ' + str(stat_time))

	print(infile+","+str(stat_locs)+","+str(stat_traces) +
            "," + str(stat_invs) + "," +
            str(stat_free_vars) + "," + str(stat_atom_data) + "," +
            str(stat_atom_pred) + "," + str(stat_pure_constrs) + "," +
            str(stat_specs) + "," + str(pre_num) + "," + str(post_num) + ","
            + str(loop_num) + ","+ str(stat_time)[:4])
    else:
        debug('Inside test mode')
        test()

if __name__ == "__main__":
    main()
