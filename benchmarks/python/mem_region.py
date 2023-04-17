import random
import pprint

class backing_file:
	def __init__(self, file_id = None):
		self.file_id = file_id

class mem_reg:
	def __init__(self, file = None, offset = 0, file_size = 0, 
		address = 0, size = 0, prev = None, next = None):
		self.file = file
		self.offset = offset
		self.file_size = file_size
		self.address = address
		self.size = size
		self.prev = prev
		self.next = next


def memory_region_init(file_, int file_offset_, int file_size_,int start_address_,int size_):
	mr = mem_reg()
  	mr.file = file_
  	mr.file_offset = file_offset_
  	mr.file_size = file_size_
  	mr.start_address = start_address_
  	mr.size = size_
  	mr.prev = None
  	mr.next = None
  	return mr

def memory_region_create_user_space_region():
  	r  = memory_region_init(None, 0, 0, 0, 1);
  	r1 = memory_region_init(None, 0, 0, 786432, 65536);
  	r.next = r1
  	r1.prev = r
  	return r

def split_memory_region(curr, int offset):
	if offset >= curr.size:
		return None

	old_next = curr.next
	nxt = None
	if offset > curr.file_size:
		nxt = memory_region_init(NULL, 0, 0, curr.start_address + offset, curr.size - offset)
	else:
		nxt = memory_region_init(curr.file, 0, 0, curr.start_address + offset, curr.size - offset)
		curr.file_size = offset

	curr.size = offset
	nxt.prev = curr
	nxt.next = old_next

	if old_next is not None:
		old_next.prev = nxt

	curr.next = nxt
	return nxt

def main():
    m = memory_region_create_user_space_region()
    mem = memory_region_init(NULL, 0, 0, 786432, 60);
    split_memory_region(mem, size)
    split_memory_region(mem, 100)

if __name__=="__main__":
	main()
