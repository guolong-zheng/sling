data node {
     int key;
     node next; };

pred ls(x,y) := emp & x=y
     \/ (exists k, u. x->node{k, u} * ls(u, y));

