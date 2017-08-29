from parse import *

class Node:
  def __init__( self, data ):
    self.data = data
    self.left = None
    self.right = None

  def __str__( self ):
    if self is None:
      return "None"
    else:
      s = ""
      self_addr = str(hex(id(self)))
      if self.left:
        l_addr = str(hex(id(self.left)))
        s += str(self.left)
      else:
        l_addr = "None"
      if self.right:
        r_addr = str(hex(id(self.right)))
        s += str(self.right)
      else:
        r_addr = "None"
      return (self_addr + " -> (" + str(self.data) + ", " + l_addr + ", " + r_addr + ")" + "\n" + s)

class Tree:
  def __init__( self, r = None ):
    self.root = r

  def _insert( self, curr, node ):
    # Invariant: curr != None
    # Invariant: isTree(curr)
    if node.data <= curr.data:
      if curr.left is None:
        curr.left = node
      else:
        self._insert(curr.left, node)
    else:
      if curr.right is None:
        curr.right = node
      else:
        self._insert(curr.right, node)
        
  def __insert( self, curr, node ):
    if curr is None:
      return node
    else:
      if node.data <= curr.data:
        curr.left = self.__insert(curr.left, node)
      else:
        curr.right = self.__insert(curr.right, node)
      return curr

  def insert( self, data ):
    node = Node(data)
    if self.root is None:
      self.root = node
    else:
      self.__insert(self.root, node)
      
  def insert2( self, data ):
    node = Node(data)
    self.root = self.__insert(self.root, node)

  def sumL( self, node ):
    # print(node)
    if node:
      return node.data + self.sumL(node.left)
    else:
      return 0

  def incL( self, node ):
    # print(node)
    if node:
      node.data += 1
      self.incL(node.left)

  def __str__( self ):
    if self.root:
      return "root = (" + str(hex(id(self.root))) + ")\n" + str(self.root)
    else:
      return "NULL"
      
  def __parse__( self, trace ):
    lines = trace.splitlines()
    
    if not lines:
      return None
    else:
      root = search("root = ({})", lines[0])[0]
      if root is None:
        return Tree()
      else:
        dict = {'None': (None, '', '')}
        for line in lines[1:]:
          n = parse("{addr} -> ({val:d}, {left}, {right})", line)
          dict[n['addr']] = (Node(n['val']), n['left'], n['right']) 
          
        for k in dict:
          if k != 'None':
            (node, l, r) = dict[k]
            node.left = dict[l][0]
            node.right = dict[r][0]
        
        t = Tree(dict[root][0])
        print(t)
        return t 

t = Tree()
t.insert2(4)
t.insert2(2)
t.insert2(1)
t.insert2(3)
t.insert2(6)
t.insert2(5)
t.insert2(7)

print(t)

t.__parse__(str(t))

# t.incL(t.root)

# print(t)

# print(t.sumL(t.root))
