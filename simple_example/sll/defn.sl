data node {
     int key;
     node next; };

pred ls(x,y) := emp & x=y
     \/ (exists u, v. x->node{v, u} * ls(u, y));

pred ll(x) := emp & x=nil
     \/ (exists v, y. x->node{v, y} * ll(y));