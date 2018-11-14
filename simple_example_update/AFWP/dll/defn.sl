data node{
    node next;
    node prev; };

data snode{
    snode next; };

pred sll(x) := emp & x=nil
        \/ (exists n. x->snode{n} * sll(n));

pred dll(hd, p, tl, n) := hd=n & tl=p
        \/ (exists x. hd->node{x, p} * dll(x, hd, tl, n));
