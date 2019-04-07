import random
import pprint

class node:
	def __init__(self, key = None, left = None, right = None):
		self.key = key
		self.left = left
		self.right = right

def insert_rec(x, k):
	if x is None:
		leaf = node(k)
		return leaf;
	elif k < x.key:
		l = x.left
		r = x.right
		tmp = insert_rec(l,k)
		x.left = tmp
		return x
	else:
		l = x.left
		r = x.right
		tmp = insert_rec(r,k)
		x.right = tmp
		return x

def create_tree(size):
	root = None
	for i in range(0,size):
		root = insert_node(root, random.randint(0, 10))
	return root

def insert_node(x, k):
	if x is None:
		leaf = node(k)
		return leaf;
	elif k < x.key:
		l = x.left
		r = x.right
		tmp = insert_rec(l,k)
		x.left = tmp
		return x
	else:
		l = x.left
		r = x.right
		tmp = insert_rec(r,k)
		x.right = tmp
		return x

def main():
	root = create_tree(5)
	insert_rec(root, random.randint(0,10))
	insert_rec(root, -100)
	insert_rec(root, 100)
	insert_rec(None, random.randint(0,10))

if __name__=="__main__":
	main()
