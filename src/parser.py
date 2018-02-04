from lark import Lark, Transformer
from seplogic import *

try:
    input = raw_input   # For Python2 compatibility
except NameError:
    pass

seplogic_grammar = ("""
    ?shform: hform -> mk_sh_true
        | pform -> mk_sh_emp
        | hform AND pform -> mk_sh
        | EX id_list DOT shform -> mk_exists_sh
        | OPAREN shform CPAREN -> mk_paren

    ?hform: hatom
        | hform STAR hatom -> mk_star

    ?hatom: EMP -> mk_emp
        | ID PTO ID OBRACE pexpr_lst CBRACE -> mk_data
        | ID OPAREN pexpr_lst CPAREN -> mk_pred

    ?pform: pfdisj
        | EX id_list DOT pform -> mk_exists
        | ALL id_list DOT pform -> mk_forall

    ?pfdisj: pfconj
        | pfdisj OR pfconj-> mk_or

    ?pfconj: pfatom
        | pfconj AND pfatom -> mk_and

    ?pfatom: prel
        | NOT pfatom -> mk_neg
        | OPAREN pform CPAREN -> mk_paren

    ?prel: TRUE -> mk_true
        | FALSE -> mk_false
        | pexpr EQ pexpr -> mk_binrel
        | pexpr NE pexpr -> mk_binrel
        | pexpr GT pexpr -> mk_binrel
        | pexpr GE pexpr -> mk_binrel
        | pexpr LT pexpr -> mk_binrel
        | pexpr LE pexpr -> mk_binrel

    ?pexpr_lst: [pexpr (COMMA pexpr)*] -> mk_list

    ?pexpr: pterm
        | pexpr ADD pterm -> mk_binop
        | pexpr SUB pterm-> mk_binop

    ?pterm: patom
        | pterm STAR patom -> mk_binop
        | pterm DIV patom -> mk_binop

    ?patom: NUM -> mk_iconst
        | NIL -> mk_nil
        | NULL -> mk_nil
        | ID -> mk_var
        | SUB patom
        | OPAREN pexpr CPAREN -> mk_paren

    ?id_list: [ID (COMMA ID)*] -> mk_list

    NIL: "nil"
    NULL: "null"
    EMP: "emp"
    PTO: "->"
    ADD: "+"
    SUB: "-"
    STAR: "*"
    DIV: "/"
    LT: "<"
    LE: "<="
    GT: ">"
    GE: ">="
    EQ: "="
    NE: "!="
    AND: "&"
    OR: "|"
    NOT: "!"
    ALL: "forall"
    EX: "exists"
    DOT: "."
    TRUE: "true"
    FALSE: "false"
    COMMA: ","
    OPAREN: "("
    CPAREN: ")"
    OBRACE: "{"
    CBRACE : "}"

    %import common.CNAME -> ID
    %import common.INT -> NUM
    %import common.WS
    %ignore WS
    """)

class TreeToSL(Transformer):
    def mk_iconst(self, (i,)):
        return IConst(int(i))

    mk_nil = lambda self, _: Null()

    def mk_var(self, (id,)):
        return Var(id)

    def mk_list(self, lst):
        return lst[0::2]

    def mk_paren(self, (oparen, e, cparen)):
        return e

    def mk_binop(self, (left, op, right)):
        return BinOp(left, op, right)

    mk_true = lambda self, _: BConst(True)

    mk_false = lambda self, _: BConst(False)

    def mk_binrel(self, (left, op, right)):
        return PBinRel(left, op, right)

    def mk_neg(self, (op, f)):
        return PNeg(f)

    def mk_and(self, (left, op, right)):
        return PConj(left, right)

    def mk_or(self, (left, op, right)):
        return PDisj(left, right)

    def mk_exists(self, (ex, vars, d, f)):
        return PExists(vars, f)

    def mk_forall(self, (all, vars, d, f)):
        return PForall(vars, f)

    mk_emp = lambda self, _: HEmp()

    def mk_data(self, (root, pto, name, obrace, args, cbrace)):
        return HData(root, name, args)

    def mk_pred(self, (name, oparen, args, cparen)):
        return HPred(name, args)

    def mk_star(self, (left, op, right)):
        return HStar(left, right)

    def mk_sh_true(self, (h,)):
        return FBase(h, BConst(True))

    def mk_sh_emp(self, (p,)):
        return FBase(HEmp(), p)

    def mk_sh(self, (h, op, p)):
        return FBase(h, p)

    def mk_exists_sh(self, (ex, vars, d, f)):
        return FExists(vars, f)

seplogic_parser = Lark(seplogic_grammar, start='shform',lexer='standard')

# text = 'exists x. !(x != (y + 1)) & x>0 | y=1'
text = 'exists y, z. emp * x->node{y} * ls(y, 1+2) & x!=null'

ast = seplogic_parser.parse(text)

print(ast)
print(ast.pretty())

f = TreeToSL().transform(ast)

print(f)
