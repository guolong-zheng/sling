import random
import pprint
	
def ret_heap(m):
    for c in m:
        ret_cell(c)

def ret_cell(c):
    while c is not None:
        print hex(id(c)) + ' ' + pprint.pformat(vars(c))
        c = c.next

class node:
	def __init__(self, key = 0, next = None):
		self.key = key
		self.next = next

def create_list(size):
	head = node( random.randint(0,10), None )
	head.next = head
	for i in range(size - 1):
		new_node = node( random.randint(0,10) )
		new_node.next = head.next
		head.next = new_node
		head = new_node
	return head

def show(x):
	head = x.next
	while x != head:
		print x.key,
		x = x.next

def lseg_insert_back(hd, tl):
    new_node = node()
	new_node.next = hd
	tl.next = new_node
	return new_node

def insert_back(x):
    next = x.next
	if(next == x):
		tl = node()
		tl.next = x
		x.next = tl
		return tl
	else:
		tl = lseg_insert_back(next, x)
		x.next = tl
		return tl

def main():
	root = create_list(5)
	res = insert_back(root)
	#show(res)

if __name__=="__main__":
	main()
