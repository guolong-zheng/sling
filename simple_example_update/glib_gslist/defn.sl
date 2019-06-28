data node {
     int key;
     node next; };

pred lseg(x,y) := emp & x=y
     \/ (exists u, v. x->node{v, u} * lseg(u, y));

pred list(x) := emp & x=nil
     \/ (exists v, y. x->node{v, y} * list(y));
