from seplogic import *

x = Var('x')
y = Var('y')
z = Var('z')
p1 = PBinRel(x, '=', y)
h1 = HEmp()
f1 = FBase(h1, p1)
print(f1)

p2 = PBinRel(x, '!=', y)
h21 = HData(x, 'node', [z])
h22 = HPred('ls', [z, y])
h2 = FBase(HStar(h21, h22), p2)
f2 = FExists(['z'], h2)
print(f2)

ls = PredDef('ls', ['x', 'y'], [f1, f2])
print(ls)
