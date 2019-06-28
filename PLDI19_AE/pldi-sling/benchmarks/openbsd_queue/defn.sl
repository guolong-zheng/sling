data node {
    node next;
    node last; };

pred ll(x) := emp & x=nil
        \/ (exists n,l. x->node{n, l} * ll(n));

pred lseg(x,y) := emp & x=y
        \/ (exists n,l. x->node{n, l} * lseg(n,y));
