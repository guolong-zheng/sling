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
	def __init__(self, key = None, next = None):
		self.key = key
		self.next = next


def insert_iter(x, k):
    if x is None:
        x = node(k)
        return x
    else:
		if k <= x.key:
			newNode = node(k,x)
			return newNode
		else:
			prv = x
			nxt = x.next
			while(nxt is not None and k > nxt.key ):
				prv = nxt
				nxt = nxt.next
			newNode = node(k,nxt)
			prv.next = newNode
			return x

def show(x):
	while x:
		print x.key,
		x = x.next
	print '\n'

def create_list(size):
	head = None
	for key in sorted(random.sample(range(0, 10), size),reverse = True):
		newNode = node( key )
		newNode.next = head
		head = newNode
	return head

def main():
	x1 = create_list(3)
	show(x1)
	res = insert_iter(x1, 5)
	show(res)

if __name__=="__main__":
	main()
