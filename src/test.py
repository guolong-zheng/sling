from seplogic import *
from trace import *
from parser import *
from model import *
from debug import *
from typ import *
from get_trace import *
from slinfer import *

def test():
    d1 = r"""
         data node { int val; node next; };

         # pred lsn(x, y, n) := emp & x=y & n=0
         # \/ (exists v, u. x->node{v, u} * lsn(u, y, n-1) & n>=1);

         pred ls(x, y) := emp & x=y
         \/ (exists v, u. x->node{v, u} * ls(u, y));

         # pred lsd(x, y) := emp & x=y
         # \/ (exists v, u. x->node{v, u} * lsd(u, y) & x!=y);

         # pred lsr(x, y) := emp & x=y
         # \/ (exists v, u. lsr(x, u) * u->node{v, y});
         """

    d2 = r"""
         data node { node next; node prev; };

         pred dll(hd,p,tl,n) := hd=n & tl=p
         \/ (exists x. hd->node{x,p} * dll(x,hd,tl,n));

         pred dlr(hd,n,tl,p) := hd=p & tl=n
         \/ (exists x. hd->node{n, x} * dlr(x,hd,tl,p));
         """

    d3 = r"""
         data node { node next; };

         # pred ll(x) := emp & x=nil
         # \/ (exists y. x->node{y} * ll(y));

         pred ls(x, y) := emp & x=y
         \/ (exists u. x->node{u} * ls(u, y));
         """

    d4 = r"""
         data node { node next; node prev; };

         pred dll(x) := emp & x=nil
         \/ (exists y. x->node{y, x} & (y=nil))
         \/ (exists y. x->node{y, x} * dll(y) & (!(y=nil)));
         """

    t1 = r"""
         0xA001 -> node{val:1; next:0xA002};
         0xA002 -> node{val:2; next:0xA003};
         0xA003 -> node{val:3; next:0xA002};
         x = 0xA001;
         y = 0xA002;
         r = 0xA002;
         z = 2;
         """

    t2 = r"""
         0xA001 -> node{val:1; next:0xA002};
         0xA002 -> node{val:2; next:0xA003};
         0xA003 -> node{val:3; next:0xA004};
         0xA004 -> node{val:4; next:0xA003};
         x = 0xA001;
         y = 0xA002;
         r = 0xA004;
         z = 0xA002;
         """

    t3a = r"""
          a = 0x0674554921088;
          b = 0x0674554921344;
          curr = 0x0674554921088;

          0x0674554921088 -> node{next:0x0674554921104; prev:nil};
          0x0674554921104 -> node{next:0x0674554921120; prev:0x0674554921088};
          0x0674554921120 -> node{next:0x0674554921328; prev:0x0674554921104};
          0x0674554921328 -> node{next:nil; prev:0x0674554921120};

          0x0674554921344 -> node{next:0x0674554921360; prev:nil};
          0x0674554921360 -> node{next:0x0674554921376; prev:0x0674554921344};
          0x0674554921376 -> node{next:0x0674554921392; prev:0x0674554921360};
          0x0674554921392 -> node{next:nil; prev:0x0674554921376};
          """

    t3b = r"""
          a = 0x0674554921088;
          b = 0x0674554921344;
          curr = 0x0674554921104;

          0x0674554921088 -> node{next:0x0674554921104; prev:nil};

          0x0674554921104 -> node{next:0x0674554921120; prev:0x0674554921088};
          0x0674554921120 -> node{next:0x0674554921328; prev:0x0674554921104};
          0x0674554921328 -> node{next:nil; prev:0x0674554921120};

          0x0674554921344 -> node{next:0x0674554921360; prev:nil};
          0x0674554921360 -> node{next:0x0674554921376; prev:0x0674554921344};
          0x0674554921376 -> node{next:0x0674554921392; prev:0x0674554921360};
          0x0674554921392 -> node{next:nil; prev:0x0674554921376};
          """

    t3c = r"""
          a = 0x0674554921088;
          b = 0x0674554921344;
          curr = 0x0674554921120;

          0x0674554921088 -> node{next:0x0674554921104; prev:nil};
          0x0674554921104 -> node{next:0x0674554921120; prev:0x0674554921088};

          0x0674554921120 -> node{next:0x0674554921328; prev:0x0674554921104};
          0x0674554921328 -> node{next:nil; prev:0x0674554921120};

          0x0674554921344 -> node{next:0x0674554921360; prev:nil};
          0x0674554921360 -> node{next:0x0674554921376; prev:0x0674554921344};
          0x0674554921376 -> node{next:0x0674554921392; prev:0x0674554921360};
          0x0674554921392 -> node{next:nil; prev:0x0674554921376};
          """

    t3d = r"""
          a = 0x001;
          b = 0x005;
          curr = 0x001;

          0x001 -> node{next:0x002; prev:nil};
          0x002 -> node{next:0x003; prev:0x001};
          0x003 -> node{next:0x004; prev:0x002};
          0x004 -> node{next:nil; prev:0x003};

          0x005 -> node{next:0x006; prev:nil};
          0x006 -> node{next:0x007; prev:0x005};
          0x007 -> node{next:0x008; prev:0x006};
          0x008 -> node{next:nil; prev:0x007};
          """

    t3e = r"""
          a = 0x001;
          b = 0x005;
          curr = 0x002;

          0x001 -> node{next:0x002; prev:nil};

          0x002 -> node{next:0x003; prev:0x001};
          0x003 -> node{next:0x004; prev:0x002};
          0x004 -> node{next:nil; prev:0x003};

          0x005 -> node{next:0x006; prev:nil};
          0x006 -> node{next:0x007; prev:0x005};
          0x007 -> node{next:0x008; prev:0x006};
          0x008 -> node{next:nil; prev:0x007};
          """

    t3f = r"""
          a = 0x001;
          b = 0x005;
          curr = 0x003;

          0x001 -> node{next:0x002; prev:nil};
          0x002 -> node{next:0x003; prev:0x001};
          0x003 -> node{next:0x004; prev:0x002};

          0x004 -> node{next:nil; prev:0x003};

          0x005 -> node{next:0x006; prev:nil};
          0x006 -> node{next:0x007; prev:0x005};
          0x007 -> node{next:0x008; prev:0x006};
          0x008 -> node{next:nil; prev:0x007};
          """

    t3g = r"""
          a = 0x001;
          b = 0x005;
          curr = 0x004;

          0x001 -> node{next:0x002; prev:nil};
          0x002 -> node{next:0x003; prev:0x001};
          0x003 -> node{next:0x004; prev:0x002};
          0x004 -> node{next:nil; prev:0x003};

          0x005 -> node{next:0x006; prev:nil};
          0x006 -> node{next:0x007; prev:0x005};
          0x007 -> node{next:0x008; prev:0x006};
          0x008 -> node{next:nil; prev:0x007};
          """

    t4 = r"""
         a = 0x1;
         0x1 -> node{next:nil; prev:nil};
         """

    s1a = r"""
          a = 0x001;
          b = 0x002;
          c = 0x003;

          0x001 -> node{next:0x001; prev:nil};
          """

    s1b = r"""
          a = 0x002;
          b = 0x002;
          c = 0x001;

          0x001 -> node{next:0x002; prev:nil};
          0x002 -> node{next:0x001; prev:0x001};
          """

    s2a = r"""
          a = 0x001;
          b = 0x001;

          0x001 -> node{next:0x001; prev:nil};
          """

    s2b = r"""
          a = 0x001;
          b = 0x001;

          0x001 -> node{next:0x002; prev:nil};
          """

    s3 = r"""
         x = 0x001;

         0x001 -> node{next:0x002};
         0x002 -> node{next:nil};
         """

    c1 = r"""
         x = 0x001;

         0x001 ->node{next:0x002};
         0x002 ->node{next:0x003};
         0x003 ->node{next:0x004};
         0x004 ->node{next:0x005};
         0x005 ->node{next:0x006};
         0x006 ->node{next:0x003};
         """

    c2 = r"""
         x = 0x003;

         0x001 ->node{next:0x002; prev:nil};
         0x002 ->node{next:0x003; prev:0x001};
         0x003 ->node{next:0x004; prev:0x002};
         0x004 ->node{next:0x005; prev:0x003};
         0x005 ->node{next:0x006; prev:0x004};
         0x006 ->node{next:nil; prev:0x005};
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
    f9 = 'ls(x,y)'
    f10 = 'ls(x,y) * ls(y,y)'
    f11 = 'lsr(x,y)'
    f12 = 'lsd(x,y)'
    f13 = 'exists u. dll(a,nil,u,nil)'
    f14 = 'a->node{nil, nil}'
    f15 = 'exists u. dll(a, nil, curr, u)'
    f16 = 'exists u, v. dll(curr, u, v, nil)'
    f17 = 'exists u1, u2, u3, u4, u5. dll(a, nil, u1, curr) * dll(curr, u2, u3, il) * dll(b, u4, u5, nil)'
    f18 = 'exists u1, u2, u3, u4, u5. dll(a, nil, u1, curr) * dll(curr, u2, u3, nil) * dll(b, u4, u5, nil) & u1=u2'
    f19 = '(exists fv109, fv110, fv111, fv114, fv115. dll(a, nil, fv109, curr) * dll(b, fv110, fv111, nil) * dll(curr, fv115, fv114, nil))'
    f20 = 'exists u, v. x->node{u} * v->node{nil}'
    f21 = 'exists u1, u2, u3. dll(a, nil, u1, curr) * dll(curr, u2, u3, nil)'
    f22 = 'exists u. ls(x, u) * ls(u, u)'
    f23 = 'exists u, v, r. dll(x,v,u,nil) * dll(r,nil,v,x)'
    f24 = 'exists u, v. dlr(x,u,v,nil)'

    defn = d2
    trace = c2
    form = f23

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
    # debug(tf)

    trace_parser = TraceParser()
    trace_ast = trace_parser.sh_parser.parse(trace)
    # debug(trace_ast)
    # debug(trace_ast.pretty())
    sh = trace_parser.transform(trace_ast)
    s = sh.stack
    h = sh.heap
    sh.add_prog(tprog)
    # debug(sh.prog)

    rctx = sh.satisfy(tf)
    debug(rctx)

    # u = s.union(h)
    # debug('stack:\n' + str(s))
    # debug('heap:\n' + str(h))
    # debug('union:\n' + str(u.dom()))

    # ff = SLInfer.infer(sh)
    # debug(ff)

    # traces = [t3d, t3e, t3f, t3g]
    traces = [c1]
    sh_lst = []
    for trace in traces:
        trace_ast = trace_parser.sh_parser.parse(trace)
        sh = trace_parser.transform(trace_ast)
        sh.add_prog(tprog)
        sh_lst.append(sh)
    # debug(sh_lst)
    # fs = SLInfer.infer_location(tprog, sh_lst)

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
    # cj = tf.mk_conj(tf)
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
