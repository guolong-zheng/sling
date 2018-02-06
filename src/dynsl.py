from seplogic import *
from trace import *
from parser import *

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

    defn_ast = seplogic_parser.parse(defn)
    # print(defn_ast)
    # print(defn_ast.pretty())
    f = TreeToSL().transform(defn_ast)
    print(f)

    traces_ast = trace_parser.parse(traces)
    # print(traces_ast)
    # print(traces_ast.pretty())
    t = TreeToTraces().transform(traces_ast)
    print(';\n'.join(map(str, t)))

if __name__ == "__main__":
    main()
