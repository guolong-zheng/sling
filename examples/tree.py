class Node:
  def __init__( self, data ):
    self.data = data
    self.left = None
    self.right = None

  def __str__( self ):
    self_addr = str(hex(id(self)))
    if self.left:
      l_addr = str(hex(id(self.left)))
    else:
      l_addr = "NULL"
    if self.right:
      r_addr = str(hex(id(self.right)))
    else:
      r_addr = "NULL"
    return (self_addr + " -> (" + str(self.data) + ", " + l_addr + ", " + r_addr + ")")

class BST:
  def __init__( self, r = None ):
    self.root = r

  def _insert( self, curr, node ):
    if curr == None:
      return node
    elif node.data <= curr.data:
      curr.left = self._insert(curr.left, node)
    else:
      curr.right = self._insert(curr.right, node)

  def insert( self, data ):
    node = Node(data)
    if self.root:
      self._insert(self.root, node)
    else:
      self.root = node

  def sumL( self, node ):
    print node
    if node:
      return node.data + self.sumL(node.left)
    else:
      return 0

  def __str__( self ):
    if self.root:
      return str(self.root) + "\n" + str(self.root.left) + "\n" + str(self.root.right)
    else:
      return "NULL"

t = BST()
t.insert(2)
t.insert(1)
t.insert(3)

# print t

print t.sumL(t.root)
