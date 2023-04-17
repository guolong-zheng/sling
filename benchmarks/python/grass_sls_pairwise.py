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
	for i in range(1, size):
		new_node = node(i, None)
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
def sls_pairwise_sum( x,  y):
	if x is None or y is None:
    	return NULL
   	curr_x = x
   	curr_y = y
   	z = node()
   	last_z = z
	z_key = (curr_x.key + curr_y.key)
  	z.key = z_key
  	z.next = None
  	while curr_x.next is not None and curr_y.next is not None:
     	tmp = last_z
    	curr_x = curr_x.next
    	curr_y = curr_y.next
    	last_z = node()
    	last_z.next = None
    	z_key = (curr_x.key + curr_y.key)
    	last_z.key = z_key
    	tmp.next = last_z
	return z

def main():
	x = create_list(10)
	y = create_list(10)
	sls_pairwise_sum(None, None)
	sls_pairwise_sum(x, None)
	sls_pairwise_sum(None, x)
	sls_pairwise_sum(x, y)

if __name__=="__main__":
	main()
