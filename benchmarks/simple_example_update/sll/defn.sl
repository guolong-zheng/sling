data node {
     int key;
     node next; };



pred ll(x) := emp & x=nil
     \/ (exists v, y. x->node{v, y} * ll(y));
