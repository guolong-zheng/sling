import random
import pprint

class node:
	def __init__(self, nxt = None, last = None):
		self.next = nxt
		self.last = last

#############
# acc func  #
#############
def create_queue(size):
	hd = node()
	hd.next = None
	hd.last = hd
	for i in range(0, size):
		new_node = node()
		new_node.next = None
		lst = hd.last
		lst.next = new_node
		hd.last = new_node
#############
# end acc   #
#############

def insert_after(head, listelm):
	elm = node()
	lenn = listelm.next
	elm.next = lenn
	if lenn is None:
		head.last = elm
	listelm.next = elm
	return head

def main():
	hd = create_queue(5)
	elm = hd.next
	insert_after(hd, elm)

if __name__=="__main__":
	main()
