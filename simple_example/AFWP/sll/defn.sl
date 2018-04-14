data node{
    node next; };

data knode{
    int key;
    knode next; };

pred sll(x) := emp & x=nil
        \/ (exists n. x->node{n} * sll(n));

pred klist(x) := emp & x=nil
        \/ (exists k, n. x->knode{k, n} * klist(n));
