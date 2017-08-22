class Node:
  def __init__( self, data ):
    self.data = data
    self.next = None

  def __str__( self ):
    self_addr = str(hex(id(self)))
    if self.next:
      next_addr = str(hex(id(self.next)))
    else:
      next_addr = "NULL"
    return (self_addr + " -> (" + str(self.data) + ", " + next_addr + ")")

class LinkedList:
  def __init__( self, h = None ):
    self.head = h

  def add( self, data ):
    node = Node( data )
    if self.head == None:
      self.head = node
    else:
      node.next = self.head
      self.head = node

  def len( self ):
    ln = 0
    p = self.head
    while p != None:
      ln += 1
      p = p.next
    return ln

  def sum( self ):
    s = 0
    p = self.head
    while p != None:
      s += p.data
      p = p.next
    return s

  def sumrec( self ):
    print self
    p = self.head
    if p:
      ll = LinkedList(p.next)
      s = ll.sumrec()
      return p.data + s
    else:
      return 0

  def last( self ):
    l = None
    p = self.head
    while p != None:
      l = p
      p = p.next
    return l

  def search( self, k ):
    p = self.head
    while p != None:
      if ( p.data == k ):
        return p
      p = p.next
    return p

  def __str__( self ):
    p = self.head
    if p:
      s = ""
      while p != None:
        s += str(p) + '\n'
        p = p.next
      return s
    else:
      return "NULL"

# example code
l = LinkedList()

l.add( 1 )
l.add( 2 )
l.add( 3 )

# l.last().next = l.head

# print l
print l.sumrec()
