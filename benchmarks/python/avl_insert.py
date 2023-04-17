import random
import pprint

class node:
	def __init__(self, key = 0, height = 0, left = None, right = None):
		self.key = key
		self.height = height
		self.left = left
		self.right = right

##################
# accessory func #
##################
def get_height(x):
	if x is None:
		return -1
	else:
		return x.height

def create_avl(size):
	root = None
	for i in range(0, size-1):
		root = insert_node(x, random.randit(0, 20))
	return root

def insert_node(x, k):
	if x is None:
		leaf = node(k, 0, None, None)
		return leaf
	else:
		xl = x.left
		xr = x.right
		if k < x.key:
			new_left = insert(xl, k)
			x.left = new_left
			res = balance(x)
			return res
		else:
			new_right = insert(xr, k)
			x.right = new_right
			res = balance(x)
			return res

def balance(x):
	lht = get_height(x.left)
	rht = get_height(x.right)
	right = x.right
	left  = x.left
	if rht == lht + 2:
		rlht = get_height(right.left)
		rrht = get_height(right.right)
		right_left = right.left
		right_right = right.right
		if rlht <= rrht:
            inc_rlht = rlht + 1
			x.height = inc_rlht
			x.right = right_left
            inc_inc_rlht = rlht + 2
			right.height = inc_inc_rlht
			right.left = x
			return right
		else:
			right_left_left = right_left.left
			right_left_right = right_left.right
            inc_lht = lht + 1
			x.height = inc_lht
			x.right = right_left_left
            inc_rrht = rrht + 1
			right.height = inc_rrht
			right.left = right_left_right
            inc_inc_lht = lht + 2
			right_left.height = inc_inc_lht
			right_left.left = x
			right_left.right = right
			return right_left
	elif lht == rht + 2:
		llht = get_height(left.left)
		lrht = get_height(left.right)
		left_left = left.left
		left_right = left.right
		if lrht <= llht:
            inc_lrht = lrht + 1
			x.height = inc_lrht
			x.left = left_right
            inc_inc_lrht = lrht + 2
			left.height = inc_inc_lrht
			left.right = x
			return left
		else:
			left_right_left = left_right.left
			left_right_right = left_right.right
            inc_rht = rht + 1
			x.height = inc_rht
			x.left   = left_right_right
            inc_llht = llht + 1
			left.height = inc_llht
			left.right = left_right_left
            inc_inc_rht = rht + 2
			left_right.height = inc_inc_rht
			left_right.left = left
			left_right.right = x
			return left_right
	elif rht == lht + 1:
        inc_rht = rht + 1
		x.height = inc_rht
		return x
	else:
        int inc_lht = lht + 1
		x.height = inc_lht
		return x

def 
##################
#  end acc func  #
##################

def insert(x, k):
	if x is None:
		leaf = node(k, 0, None, None)
		return leaf
	else:
		xl = x.left
		xr = x.right
		if k < x.key:
			new_left = insert(xl, k)
			x.left = new_left
			res = balance(x)
			return res
		else:
			new_right = insert(xr, k)
			x.right = new_right
			res = balance(x)
			return res

def main():
	root = create_avl(10)
	insert(root, random.randit(0, 20))
	insert(root, 100)
	insert(root, -100)
	insert(None, random.randit(0, 20))

if __name__=="__main__":
	main()
