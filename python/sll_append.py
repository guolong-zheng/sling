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


def append(x1, x2):
    ret_heap([x1, x2])
    if x1 is None:
	    return x2
    else:
	    tmp = append(x1.next, x2)
	    x1.next = tmp
	    return x1

def show(x):
	while x:
		print x.key,
		x = x.next
	print '\n'

def create_list(size):
	head = node( random.randint(0,10), None )
	for i in range(size - 1):
		newNode = node( random.randint(0,10) )
		newNode.next = head
		head = newNode
	return head

def main():
	x1 = create_list(3)
	#show(x1)
	x2 = create_list(5)
	#show(x2)
	res = append(x1, x2)
	#show(res)

if __name__=="__main__":
	main()
