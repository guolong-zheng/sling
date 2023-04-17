data node{
    int key;
    node next; };

pred sll(x) := emp & x=nil
        \/ (exists k, n. x->node{k,n} * sll(n));
