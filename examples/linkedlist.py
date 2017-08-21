class Node:
  def __init__( self, data ):
    self.data = data
    self.next = None
    
  def __str__( self ):
    return str(id(self)) + " -> " + str(self.data) + ", " + str(id(self.next)) + '\n'

class LinkedList:
  def __init__( self ):
    self.head = None    

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
    s = ""
    p = self.head
    while p != None:
      s += str(p) + '\n'
      p = p.next
    return s

# example code
l = LinkedList()

l.add( 1 )
l.add( 2 )
l.add( 3 )

# l.last().next = l.head

print l
print l.sum()
