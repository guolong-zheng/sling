import random
import pprint

class node:
	def __init__(self, key = 0, left = None, right = None):
		self.key = key
		self.left = left
		self.right = right

def inorder(x, n):
    if x is None:
        return n
    else:
        n1 = inorder(x.left, n)
        x.key = n1
        n2 = n1 + 1
        n3 = inroder(x.right, n2)
        return n3

def create_tree(size):
    root = None
    for i in range(0, size):
        new_node = node(random.randint(0, 10), None, None)
        root = insert(root, new_node)
    return root

def insert(root, node):
    if root is None:
        return node
    else:
        t = random.randint(-5, 5)
        if t > 0:
            root.left = insert(root.left, node)
        else:
            root.right = insert(root.right, node)
        return root

def main():
	root = create_tree(5)
	inorder(root, 0)
    inorder(None, 0)

if __name__=="__main__":
	main()
