import random
import pprint

class node:
	def __init__(self, nxt = None, prev = None):
		self.next = nxt
		self.prev = prev

##################
# accessory func #
##################
def create_list(size):
	root = None
	tl = root
	for i in range(1, size):
		new_node = node()
		if root is None:
			root = new_node
			tl = root
		else:
			tl.next = new_node
			new_node.prev = tl
			tl = new_node
	return root

##################
#  end acc func  #
##################

def dl_insert(lst, elt):
	if lst is None:
		return elt
	else:
		nondet = 1
		curr = lst
		while nondet > 0 and curr.next is not None:
			nondet = random.randint(-2, 5)
			curr = curr.next
		curr_next = curr.next
		elt.next = curr_next
		if curr_next is not None:
			curr_next.prev = None
		curr.next = elt
		elt.prev = curr
		return lst

def main():
	root = create_list(10)
	elt = node()
	insert(root, elt)
	insert(None, elt)

if __name__=="__main__":
	main()
