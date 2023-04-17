data node {
     node next; };

pred ls(x,y) := emp & x=y
     \/ (exists u. x->node{u} * ls(u, y));

pred ll(x) := emp & x=nil
     \/ (exists y. x->node{y} * ll(y));
