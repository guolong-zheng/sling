import random
import pprint
	
class slave_item:
	def __init__(self, nxt = None, prev = None):
		self.next = nxt
		self.prev = prev

def insert_slave(x):
	item = slave_item(None, None)
	nxt = x
	item.next = nxt
	if nxt is not None:
		nxt.prev = item
	return item

def create_slave(n):
	dll = None
	while n > 0:
		n = n - 1
		dll = insert_slave(dll)
	return dll

def main():
	create_slave(5)

if __name__=="__main__":
	main()
