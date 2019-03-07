from z3 import *

x = Int('x')
y = Int('y')
z = Int('z')
s = Solver()
print(x+1)
print(s.check())
print(s.model())
