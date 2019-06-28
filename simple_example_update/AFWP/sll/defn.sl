data node{
    node next; };

data knode{
    int key;
    knode next; };

pred sll(x) := emp & x=nil
        \/ (exists n. x->node{n} * sll(n));

pred lseg(x, y) := emp & x=y
        \/ (exists n. x->node{n} * lseg(n, y));

pred klist(x) := emp & x=nil
        \/ (exists k, n. x->knode{k, n} * klist(n));

pred klseg(x, y) := emp & x=y
        \/ (exists k, n. x->knode{k, n} * klseg(n, y));
