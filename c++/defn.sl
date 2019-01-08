data node {
     int key;
     node next; };



pred lseg(x,y) := emp & x=y
     \/ (exists v, n. x->node{v, n} * lseg(n, y));
