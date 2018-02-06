from seplogic import *
from trace import *
from parser import *
from model_checker import *

def main():
    defn = """
           data node { int val; node next; };

           pred ls(x,y,n) := emp & x=y & n=0
           \/ (exists v, u. x->node{v, u} * ls(u,y,n-1) & n>=1);
           """

    traces = """
             0xA001 -> node{val:1; next:0xA002};
             0xA002 -> node{val:2; next:0xA003};
             0xA003 -> node{val:3; next:0xA002};
             x = 0xA001;
             y = 0xA002;
             """

    form = "x!=y"

    seplogic_parser = SepLogicParser()
    defn_ast = seplogic_parser.defn_parser.parse(defn)
    # print(defn_ast)
    # print(defn_ast.pretty())
    prog = seplogic_parser.transform(defn_ast)
    print(prog)

    form_ast = seplogic_parser.sl_parser.parse(form)
    f = seplogic_parser.transform(form_ast)
    print(f)

    trace_parser = TraceParser()
    traces_ast = trace_parser.sh_parser.parse(traces)
    # print(traces_ast)
    # print(traces_ast.pretty())
    s, h = trace_parser.transform(traces_ast)
    print(s)
    print(';\n'.join(map(str, h)))

    mc = SHModelChecker()
    # mc.check(t, f)

if __name__ == "__main__":
    main()
