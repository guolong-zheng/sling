import random
import pprint

class node:
	def __init__(self, key = 0, next = None, prev = None):
		self.key = key
		self.next = next
		self.prev = prev

#############
# acc func  #
#############
def create_list(size):
	hd = None
	tl = hd
	for i in range(0, size):
		new_node = node(i, None, None)
		if hd is None:
			hd = new_node
			tl = hd
		else:
			new_node.prev = tl
			tl.next = new_node
			tl = new_node
	return hd
#############
# end acc   #
#############

def prepend(lst, data, p):
	ret = node(data, lst, p)
	if lst is not None:
		lst.prev = ret
	if p is not None:
		p.next = ret
	return ret

def main():
	hd = create_list(5)
	p = hd.prev
	prepend(hd, random.randint(0, 10), p)
	p = (hd.next).next
	prepend(hd, random.randint(0, 10), p)
	prepend(None, random.randint(0, 10), p)

if __name__=="__main__":
	main()
