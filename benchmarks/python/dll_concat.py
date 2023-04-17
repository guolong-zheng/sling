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
	def __init__(self, key = None, next = None, prev = None):
		self.key = key
		self.next = next
		self.prev = prev

def create_list(size):
	head = node( random.randint(0,10), None, None )
	for i in range(size - 1):
		newNode = node( random.randint(0,10) )
		newNode.next = head
		head.prev = newNode
		head = newNode
	return head

def concat(a, b):
	if a is None:
		return b
	else:
		curr = a
		while curr.next is not None:
			curr = curr.next
		
		curr.next = b
		if b is not None:
			b.prev = curr
		
		return a

def show(a):
	cur = a
	while cur is not None:
		print cur.key,
		cur = cur.next

def main():
	x1 = create_list(5)
	show(x1)
	x2 = create_list(5)
	#show(x2)
	res = concat(x1, x2)
	#show(res)

if __name__=="__main__":
	main()
