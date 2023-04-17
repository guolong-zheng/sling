import random
import pprint

class node:
	def __init__(self, m = False , c = False, l = None, r = None):
		self.m = m
		self.c = c
		self.l = l
		self.r = r

def schorr_waite( root):
	t = root
	p = 0
	while p != 0 or (t != 0 and not (t.m))):
		if(t == 0 or t.m):
			if(p.c):
				q = t
				t = p
				p = p.r
				t.r = q
			else:
				q = t
				t = p.r
				p.r = p.l
				p.l = q
				p.c = True
		else:
			q = p
			p = t
			t = t.l
			p.l = q
			p.m = True
			p.c = False

def makeNode():
	n = node(False, False, None, None)
	return n

def main():
	root = makeNode()
	for i in range(1, 10):
		n = root
		p = None
		j = 0
		while n is not None:
			j = random.randint(-5, 5)
			p = n
			if j > 0:
				n = n.l
			else
				n = n.r
		if j > 0:
			p.l = makeNode()
		else:
			p.r = makeNode()
		i = i + 1
	schorr_waite(root)

if __name__=="__main__":
	main()
