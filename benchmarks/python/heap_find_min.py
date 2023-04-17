import random
import pprint

class node:
	def __init__(self, key = None, order = None, children = None, sibling = None):
		self.key = key
		self.order = order
		self.children = children
		self.sibling = sibling

#############
# acc func  #
#############
def create_heap(size):
	root = node()
	for i in range(1, size):
		new_node = node(random.randint(0, 20), 0, None, None)
		root = merge(root, new_node)

def merge(x, y):
	if x is None:
		return y
	elif y is None:
		return x
	elif x.order == y.order:
		xs = x.sibling
		ys = y.sibling
		z = merge(xs, ys)
		ord1 = x.order
		ord2 = y.order
		if ord1 <= ord2:
			xchld = x.children
			y.sibling = xchld
			x.children = ys
			x.sibling = z
			x.order = ord1 + 1
			return x
		else:
			ychld = y.children
            x.sibling = ychld
            y.children = x
            y.sibling = z
            y.order = ord2 + 1
            return y
	elif y.order < x.order:
		xs = x.sibling
		z = merge(xs, y)
		ord1 = x.order
		ord2 = y.order
		zord = z.order
		zk = z.key
		xk = x.key

		if ord1 == zord and zk <= xk:
			zchld = z.children
			x.sibling = zchld
			z.children = x
			z.order = zord + 1
			return z
		elif ord1 == zord and xk < zk:
			zsib = z.sibling
			x.sibling = zsib
			xchld = x.children
			z.sibling = xchld
			x.children = z
			x.order = ord1 + 1
			return x
		else:
			x.sibling = z
			return x
	else:
		ys = y.sibling
		z = merge(ys, x)
		ord1 = x.order
		ord2 = y.order
		zord = z.order
		zk = z.key
		yk = y.key
		if ord2 == zord and zk <= yk:
			zchld = z.children
			y.sibling = zchld
			z.children = y
			z.order = zord + 1
			return z
		elif ord2 == zord and yk < zk:
			zsib = z.sibling
			y.sibling = zsib
			ychld = y.children
			z.sibling = ychld
			y.children = z
			y.order = ord2 + 1
			return x
		else:
			y.sibling = z
			return y
#############
# end acc   #
#############

def find_min(x):
	xs = x.sibling
	xk = x.key
	if xs is None:
		return xk
	else
	y = find_min(xs)
	if xk <= y:
		return xk
	else:
		return y

def main():
	x = create_heap(5)
	find_min(x)

if __name__=="__main__":
	main()
