import random
import pprint

class node:
	def __init__(self, key = 0, nxt = None):
		self.key = key
		self.next = nxt

##################
# accessory func #
##################
def create_list(size):
	root = None
	tl = root
	for i in range(0, size):
		new_node = node(i, None)
		if root is None:
			root = new_node
			tl = root
		else:
			pos.next = new_node
			pos = new_node
	return root
##################
#  end acc func  #
##################

def sort_merge(l1, l2):
	lst = node()
    y = None
	lst.key = -100
	lst.next = y
	l = lst
    lst_next =lst.next
	while l1 is not None and l2 is not None:
		if l1.key <= l2.key:
			l.next = l1
			l1 = l1.next
		else:
			l.next = l2
			l2 = l2.next
		l = l.next
    	if y is None:
      		y = l
		l.next = None

	if l1 is not None:
		l.next = l1
	else:
		l.next = l2

	return list_next

def main():
	lst1 = create_list(5)
	lst2 = create_list(5)
	sort_merge(lst1, lst2)
	sort_merge(None, None)
	sort_merge(create_list(5), None)
	sort_merge(None, create_list(5))

if __name__=="__main__":
	main()
