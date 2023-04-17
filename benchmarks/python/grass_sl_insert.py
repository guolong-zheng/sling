import random
import pprint

class node:
	def __init__(self, nxt = None):
		self.next = nxt

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
			tl = new_node
	return root

##################
#  end acc func  #
##################

def sl_insert(lst, elt):
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
		curr.next = elt
		return lst

def main():
	root = create_list(10)
	elt = node()
	insert(root, elt)
	insert(None, elt)

if __name__=="__main__":
	main()
