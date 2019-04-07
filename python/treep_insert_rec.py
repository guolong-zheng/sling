import random
import pprint

class node:
	def __init__(self, key = 0, prio = 0, left = None, right = None):
		self.key = key
		self.prio = prio
		self.left = left
		self.right = right

def insert_rec(x, k, p):
	if x is None:
		leaf = node(k, p)
		return leaf;
	elif k < x.key:
		xl = x.left
		xr = x.right
		tmp = insert_rec(xl, k, p)
		if tmp.prio <= x.prio:
			x.left = tmp
			return x
		else:
			lr = tmp.right
			x.left = lr
			tmp.right = xl
			return tmp
	else:
		xl = x.left
		xr = x.right
		tmp = insert_rec(xr, k, p)
		if tmp.prio <= x.prio:
			x.right = tmp
			return x
		else:
			rl = tmp.left
			x.right = rl
			tmp.left = xl
			return tmp

def create_tree(size):
	root = None
	for i in range(0,size-3):
		root = insert_rec(root, random.randint(0, 10), i)
	root = insert_rec(root, random.randint(0, 10), -5)
	root = insert_rec(root, random.randint(0, 10), -2)
	root = insert_rec(root, random.randint(0, 10), -4)
	return root

def insert_node(x, k, p):
	if x is None:
		leaf = node(k, p)
		return leaf;
	elif k < x.key:
		xl = x.left
		xr = x.right
		tmp = insert_rec(xl, k, p)
		if tmp.prio <= x.prio:
			x.left = tmp
			return x
		else:
			lr = tmp.right
			x.left = lr
			tmp.right = xl
			return tmp
	else:
		xl = x.left
		xr = x.right
		tmp = insert_rec(xr, k, p)
		if tmp.prio <= x.prio:
			x.right = tmp
			return x
		else:
			rl = tmp.left
			x.right = rl
			tmp.left = xl
			return tmp

def main():
	root = create_tree(5)
	insert_node(root, random.randint(0,10))
	insert_node(root, -100)
	insert_node(root, 100)
	insert_node(None, random.randint(0,10))

if __name__=="__main__":
	main()
