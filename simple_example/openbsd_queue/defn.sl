data node {
    node next;
    node last; };

pred ll(x, l) := emp & x=nil
        \/ (exists n. x->node{n, l} * ll(n,l));
