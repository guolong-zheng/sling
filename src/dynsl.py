from seplogic import *
from trace import *
from parser import *
from model_checker import *
from debug import *
from typ import *
from get_trace import *
import argparse

def main():
    aparser = argparse.ArgumentParser(description='SLING')
    ag = aparser.add_argument

    ag('--input', '-input',
       dest='in_file')

    ag('--breaks', '-breaks',
       dest='breaks', nargs='+',
       type=int)

    ag('--trace', '-trace',
       dest='trace', type=open)

    ag('--def', '-def',
       dest='pred', type=open)

    ag("--nomp", "-nomp",
       action="store_true")

    args = aparser.parse_args()

    import settings
    settings.doMP = not args.nomp

    input_file = args.in_file
    bps = args.breaks
    traces = get_traces(input_file, bps)
    for t in traces:
        print "trace at location: %s" % t
        tr = traces[t]
        for x in tr:
            st = x.stack
            hp = x.heap
            print "stack is:"
            for s in st:
                print st[s]
            print "heap is:"
            for h in hp:
                print hp[h]

    defn = args.pred
    traces = args.trace

    debug(traces)

    defn = r"""
           data node { int val; node next; };

           pred ls(x,y,n) := emp & x=y & n=0
           \/ (exists v, u. x->node{v, u} * ls(u,y,n-1) & n>=1);
           """

    traces = r"""
             0xA001 -> node{val:1; next:0xA002};
             0xA002 -> node{val:2; next:0xA003};
             0xA003 -> node{val:3; next:0xA002};
             x = 0xA001;
             y = 0xA002;
             z = 2;
             """

    # form = "x->node{z-1, u}"
    # form = r"""exists u, v, r, n1.
    #            u->node{v, r} * x->node{v-2, y} * ls(y, u, n1)
    #            & v>1 & r=y & n1=1"""
    # form = 'exists u, v, r, n. x->node{v, r} * ls(r, u, n) & v>1 & n>1'
    # form = 'x->node{1, y}'
    # form = "z=2"

    f1 = 'x->node{v, y} & v>0'
    f2 = 'x->node{v1, y} * y->node{v2, r} & v1+v2<0'
    f3 = 'x->node{v, y} * ls(y, y, n) & n>=2'
    f4 = 'exists u, v, r. u->node{v, r} & v>1 & r=y'
    f5 = 'exists u, n. ls(x, u, n)'
    f6 = 'exists u, v. u->node{v, y} & v>=1 & u=x'
    f7 = 'exists u, v, r. u->node{v, r} & v>=1 & r=y'
    f8 = 'exists u, v, r, n. ls(x, u, n) * u->node{v, r} & v>1'

    form = f8

    seplogic_parser = SepLogicParser()
    defn_ast = seplogic_parser.defn_parser.parse(defn)
    # print(defn_ast)
    # print(defn_ast.pretty())
    prog = seplogic_parser.transform(defn_ast)
    # debug(prog)

    form_ast = seplogic_parser.sl_parser.parse(form)
    f = seplogic_parser.transform(form_ast)
    debug(f)

    type_infer = TInfer()
    tprog = type_infer.infer(prog)
    # debug(prog)
    debug(tprog)
    tf = type_infer.infer(f)
    # debug(f)
    debug(tf)

    trace_parser = TraceParser()
    traces_ast = trace_parser.sh_parser.parse(traces)
    # debug(traces_ast)
    # debug(traces_ast.pretty())
    sh = trace_parser.transform(traces_ast)
    s = sh.stack
    h = sh.heap
    sh.add_prog(tprog)
    debug(sh.prog)
    rctx = sh.satisfy(tf)
    # u = s.union(h)
    # debug('stack:\n' + str(s))
    # debug('heap:\n' + str(h))
    # debug('union:\n' + str(u.dom()))

    # mc = SHModelChecker()
    # mc.check(t, f)

    r1 = PBinRel(BinOp(Var('z'), '+', IConst(2)), '!=', IConst(1))
    r2 = PBinRel(BinOp(Var('y'), '*', IConst(2)), '=', IConst(2))
    r3 = PExists([Var('z')], PConj(
                 (PBinRel(Var('z'), '=', BinOp(Var('y'), '-', IConst(1)))),
                 (PBinRel(Var('z'), '>', IConst(1)))))
    r4 = PExists([Var('z')], PDisj(r3, PNeg(r1)))
    r5 = PExists([Var('x')],
                 PForall([Var('m')],
                         PConj(PBinRel(Var('x'), '>', Var('m')),
                               PBinRel(Var('n'), '>', Var('m')))))
    r = PConj(r3, r2)
    # debug(r3.fv())
    r4r = r4.rename()
    # debug(r4)
    # debug(r4r)
    # debug(s.evaluate(PNeg(r4)))
    cj = tf.mk_conj(tf)
    # debug(cj)
    # debug(s.eval(BinOp(Var('z'), '+', IConst(2)), 'eval'))
    # debug(s.eval(BinOp(Var('n'), '+', IConst(2)), 'trans'))
    # sst = {'z':Var('y')}
    # sst = {'y':Var('z')}
    # r6 = r4.subst(sst)
    # debug(r4)
    # debug(r6)
    # sh.satisfy(r5)

    # r7 = r4.rename()
    # debug(r4)
    # debug(r7)

    # p1 = prog.rename()
    # debug(prog)
    # debug(p1)

if __name__ == "__main__":
    main()
