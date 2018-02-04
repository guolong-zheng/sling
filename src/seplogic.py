class ArithOp:
    ADD = '+'
    SUB = '-'
    MUL = '*'
    DIV = '/'

    @classmethod
    def arith_op(self, s):
        if s == '+':
            return self.ADD
        elif s == '-':
            return self.SUB
        elif s == '*':
            return self.MUL
        elif s == '/':
            return self.DIV
        else:
            raise SyntaxError('Unexpected arithmetic operator ' + s)

class RelOp:
    LT = '<'
    LE = '<='
    GT = '>'
    GE = '>='
    EQ = '='
    NE = '!='

    @classmethod
    def rel_op(self, s):
        if s == '<':
            return self.LT
        elif s == '<=':
            return self.LE
        elif s == '>':
            return self.GT
        elif s == '>=':
            return self.GE
        elif s == '=':
            return self.EQ
        elif s == '!=':
            return self.NE
        else:
            raise SyntaxError('Unexpected relational operator ' + s)


class SepLogic(object):
    pass

class Expr(SepLogic):
    pass

class Null(Expr):
    def __str__(self):
        return 'nil'

class Var(Expr):
    def __init__(self, id, is_primed = False):
        self.id = id
        self.is_primed = is_primed

    def __str__(self):
        return (self.id + ('\'' if self.is_primed else ''))

class IConst(Expr):
    def __init__(self, i):
        self.val = i

    def __str__(self):
        return str(self.val)

class BinOp(Expr):
    def __init__(self, left, op, right):
        self.op = ArithOp.arith_op(op)
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

class PRel(SepLogic):
    pass

class BConst(PRel):
    def __init__(self, b):
        self.val = b

    def __str__(self):
        return str(self.val)

class PBinRel(PRel):
    def __init__(self, left, op, right):
        self.op = RelOp.rel_op(op)
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + str(self.op) + str(self.right)

class PPred(PRel):
    def __init__(self, id, args):
        self.id = id
        self.args = args

    def __str__(self):
        return (self.id + '(' +
               ', '.join(map(str, self.args)) + ')')

class PNeg(PRel):
    def __init__(self, f):
        self.form = f

    def __str__(self):
        return 'not(' + str(self.form) + ')'

class PConj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + ' & ' + str(self.right)

class PDisj(PRel):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.left) + ' | ' + str(self.right)

class PForall(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f

    def __str__(self):
        return ('(forall ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

class PExists(PRel):
    def __init__(self, vars, f):
        self.vars = vars
        self.form = f

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

class HRel(SepLogic):
    pass

class HAtom(HRel):
    pass

class HEmp(HAtom):
    def __init__(self):
        pass

    def __str__(self):
        return 'emp'

class HData(HAtom):
    def __init__(self, root, name, args):
        self.root = root
        self.name = name
        self.args = args

    def __str__(self):
        return (str(self.root) + '->' + self.name + '{' +
                (', '.join(map(str, self.args))) + '}')

class HPred(HAtom):
    def __init__(self, name, args):
        self.name = name
        self.args = args

    def __str__(self):
        return (self.name + '(' + (', '.join(map(str, self.args))) + ')')

class HStar(HRel):
    def __init__(self, left, right):
        if isinstance(left, HRel) and isinstance(right, HRel):
            self.left = left
            self.right = right
        else:
            raise SyntaxError('left or right is not a heap relation')

    def __str__(self):
        return (str(self.left) + ' * ' + str(self.right))

class SH(SepLogic):
    pass

class FBase(SH):
    def __init__(self, heap, pure):
        is_HRel = isinstance(heap, HRel)
        is_PRel = isinstance(pure, PRel)
        if not is_HRel:
            raise SyntaxError(str(heap) + ' is not a heap formula')
        elif not is_PRel:
            raise SyntaxError(str(pure) + ' is not a pure formula')
        else:
            self.heap = heap
            self.pure = pure

    def __str__(self):
        return (str(self.heap) + ' /\ ' + str(self.pure))

class FExists(SH):
    def __init__(self, vars, f):
        if isinstance(f, SH):
            self.vars = vars
            self.form = f
        else:
            raise SyntaxError(str(f) + ' is not a symbolic-heap formula')

    def __str__(self):
        return ('(exists ' + (', '.join(map(str, self.vars))) +
                '. ' + str(self.form) + ')')

class PredDef(SepLogic):
    def __init__(self, name, params, cases):
        self.name = name
        self.params = params
        self.cases = cases

    def __str__(self):
        return (self.name + '(' + (', '.join(map(str, self.params))) + ')' +
                ' == ' + (' \/ '.join(map(str, self.cases))))
