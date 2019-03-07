data node{
  struct node * next;
  struct node * left;
  struct node * right;
  struct node * tree;
  int key; } ;

pred list(x) := emp & x=nil
        \/ (exists n,l,r,t,k. x->node{n,l,r,t,k} * list(n) & l=nil & r=nil & t=nil);
