data node {
    node next; };

pred ls(x,y) := emp & x=y
         \/ (exists u. x->node{u} * ls(u, y));
